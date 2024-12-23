#include "../../header/BookInfoClass.h"

void BookInfoClass::selectBookList(int pageIdx) {
    try {
        int pageStartNum = (pageIdx - 1) * 10;
        int pageEndNum = pageIdx * 10;

        cout << "Page start: " << pageStartNum << "\n";
        cout << "Page end: " << pageEndNum << "\n";

        string queryString = "select @ROWNUM:=@ROWNUM+1 AS ROWNUM"
                             " , A.*"
                             "from ("
                             " select bi.book_seq bookSeq"
                             "  , bi.book_nm bookName"
                             "  , bi.book_author bookAuth"
                             "  , case when b.book_status = 1 then '대여중'"
                             "     else '대여가능'"
                             "    end bookStatus"
                             " from book_info bi"
                             " left outer join book b"
                             "  on bi.book_seq = b.user_seq) A"
                             " , (SELECT @ROWNUM:=0) R "
                             "LIMIT ?, ?";
        unique_ptr<PreparedStatement> stmnt(conn->prepareStatement(queryString));
        stmnt->setInt(1, pageStartNum);
        stmnt->setInt(2, pageEndNum);
        ResultSet *res = stmnt->executeQuery();
        res->last();
        int totalRow = res->getRow();
        res->beforeFirst();

        if (totalRow != 0){
            while (res->next()) {
                cout << "번호 : " << res->getInt("ROWNUM") << endl;
                cout << "도서 일련번호 : " << res->getInt("bookSeq") << endl;
                cout << "도서명 : " << res->getString("bookName") << endl;
                cout << "저자 : " << res->getString("bookAuth") << endl;
                cout << "대여상태 : " << res->getString("bookStatus") << endl;
            }
        }else {
            cout << "조회된 내용이 없습니다." << endl;
        }
    }catch (SQLException e) {
        cerr << "Error (BookInfoClass::selectBookList) : " << e.what() << endl;
    }
}

void BookInfoClass::selectBookInfo(int bookSeq) {
    try {
        string queryString = "select bi.book_seq bookSeq"
                             ", bi.book_nm bookName"
                             ", bi.book_room_nm bookRoomNm"
                             ", bi.book_serial_num bookSerialNumber"
                             ", bi.book_author bookAuth"
                             ", bi.book_publisher bookPublisher"
                             ", bi.book_pub_year bookPubYear"
                             ", case when b.book_status = 1 then '대여중'"
                             "    else '대여가능'"
                             "  end bookStatus "
                             "from book_info bi "
                             "left outer join book b "
                             "on bi.book_seq = b.book_seq"
                             "where bi.book_seq = ?";
        unique_ptr<PreparedStatement> stmnt(conn->prepareStatement(queryString));
        stmnt->setInt(1, bookSeq);
        ResultSet *res = stmnt->executeQuery();
        res->next();

        cout << "도서 일련번호 : " << res->getString("bookSeq") << endl;
        cout << "도서명 : " << res->getString("bookName") << endl;
        cout << "책 위치 : " << res->getString("bookRoomName") << endl;
        cout << "책 시리얼넘버 : " << res->getString("bookSerialNumber") << endl;
        cout << "저자 : " << res->getString("bookAuthor") << endl;
        cout << "출판사 : " << res->getString("bookPublisher") << endl;
        cout << "출판년도 : " << res->getString("bookPubYear") << endl;
        cout << "대여상태 : " << res->getString("bookStatus") << endl;

    }catch (SQLException e) {
        cerr << "Error (BookInfoClass::selectBookInfo) : " << e.what() << endl;
    }
}

void BookInfoClass::checkOut(int userSeq, int bookSeq) {
    try {
        string queryString = "insert into book "
                             "values("
                             " default"
                             " , ?"
                             " , ?"
                             " , CURRENT_TIMESTAMP()"
                             " , date_add(NOW(), interval +? day)"
                             " , 1)";
        unique_ptr<PreparedStatement> stmnt(conn->prepareStatement(queryString));
        stmnt->setInt(1, bookSeq);
        stmnt->setInt(2, userSeq);
        stmnt->executeQuery();
    }catch (SQLException e) {
        cerr << "Error (BookInfoClass::checkOut) : " << e.what() << endl;
    }
}

void BookInfoClass::checkIn(int userSeq, int bookSeq) {
    try {
        string queryString = "update book set book_status = 0 where book_seq = ? and user_seq = ?";
        unique_ptr<PreparedStatement> stmnt(conn->prepareStatement(queryString));
        stmnt->setInt(1, bookSeq);
        stmnt->setInt(2, userSeq);
        stmnt->executeQuery();
    }catch (SQLException e) {
        cerr << "Error (BookInfoClass::checkIn) : " << e.what() << endl;
    }
}
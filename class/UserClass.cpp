#include "../header/UserClass.h"

UserClass::UserClass() {
    loginUserInfo = new UserInfo();
}

UserClass::~UserClass() {
    delete loginUserInfo;
}


bool UserClass::login(string userId, string userPassword){
    try {
        // createStaemet 객체 생성
        string queryString = "select count(1) cnt"
                             "from user "
                             "where user_id = ? "
                             " and user_pwd = ?";
        unique_ptr<PreparedStatement>  stmnt(conn->prepareStatement(queryString));
        stmnt->setString(1, userId);
        stmnt->setString(2, userPassword);

        // 쿼리를 실행
        ResultSet *res = stmnt->executeQuery();
        res->next();
        if (res->getInt("cnt") > 0) {
            cout << "로그인 성공" << endl;
            return true;
        }else {
            cout << "아이디나 패스워드가 잘못됨" << endl;
            return false;
        }
        // 실패시 오류 메세지 반환
    } catch(SQLException& e){
        cerr << "Error (UserClass::login) : " << e.what() << endl;
        return false;
    }
}

bool UserClass::join(UserInfo joinInfo) {
    string queryString = "";
    unique_ptr<PreparedStatement>  stmnt;
    try{
        //필수값 및 성별 값 유효성 체크
        if (joinInfo.userId == "" || joinInfo.userPwd == "" || joinInfo.userName == "" || joinInfo.userTel == ""
            || (joinInfo.userGender != 0 && joinInfo.userGender != 1) ) {
            cout << "잘못된 정보입니다" << endl;
            return false;
        }else {
            queryString = "select count(1) cnt"
                          "from user "
                          "where user_id = ?";
            stmnt = unique_ptr<PreparedStatement>(conn->prepareStatement(queryString));
            stmnt->setString(1, joinInfo.userId);
            ResultSet *res = stmnt->executeQuery();
            res->next();
            if (res->getInt("cnt") > 0) {
                cout << "이미 등록된 아이디입니다" << endl;
            }else {
                queryString = "insert into user "
                              "values ("
                              "   default"  //user_seq
                              " , ?"        //user_id
                              " , ?"        //user_pwd
                              " , ?"        //user_name
                              " , ?"        //user_birth
                              " , ?"        //user_gender
                              " , ?"        //user_tel
                              " , ?"        //user_addr
                              " , 1"        //user_grade
                              " , default"  //user_join_dt
                              " , null)";   //user_upt_dt
                stmnt = unique_ptr<PreparedStatement>(conn->prepareStatement(queryString));
                stmnt->setString(1, joinInfo.userId);
                stmnt->setString(2, joinInfo.userPwd);
                stmnt->setString(3, joinInfo.userName);
                stmnt->setString(4, joinInfo.userBirth);
                stmnt->setInt(5, joinInfo.userGender);
                stmnt->setString(6, joinInfo.userTel);
                stmnt->setString(7, joinInfo.userAddress);

                stmnt->executeQuery();

                cout << "회원가입 완료 !!" << endl;
                return true;
            }
        }
    }catch(SQLException& e){
        cerr << "Error (UserClass::join) : " << e.what() << endl;
        return false;
    }
}

void UserClass::selectUserInfo() {
    loginUserInfo->userId = "admin";
    try {
        string queryString  = "select user_seq userSeq"
                              "     , user_id userId"
                              "     , user_pwd userPwd"
                              "     , user_name userName"
                              "     , user_birth userBirth"
                              "     , user_gender userGender"
                              "     , user_tel userTel"
                              "     , user_addr userAddr"
                              "     , user_grade userGrade "
                              "from user "
                              "where user_id = ?";
        unique_ptr<PreparedStatement> stmnt(conn->prepareStatement(queryString));
        stmnt->setString(1, loginUserInfo->userId);
        ResultSet *res = stmnt->executeQuery();
        res->next();
        cout << "일련번호 : " << res->getInt("userSeq") << endl;
        cout << "아이디 : " << res->getString("userId") << endl;
        cout << "비밀번호 : " << res->getString("userPwd") << endl;
        cout << "이름 : " << res->getString("userName") << endl;
        cout << "생년월일 : " << res->getString("userBirth") << endl;
        cout << "성별 : " << (res->getInt("userGender") == 0 ? "남자" : "여자") << endl;
        cout << "연락처 : " << res->getString("userTel") << endl;
        cout << "주소 : " << res->getString("userAddr") << endl;
        cout << "회원등급 : " << res->getInt("userGrade") << endl;
    }catch(SQLException& e) {
        cerr << "Error (UserClass::selectUserInfo) : " << e.what() << endl;
    }
}

void UserClass::selectCheckOutBookList() {
    try {
        string queryString  = "select book.book_seq bookSeq"
                              " , book.book_nm bookName"
                              " , book.book_author bookAuth"
                              " , b.book_status bookStatus "
                              "from book b "
                              "left outer join book_info book"
                              " on book.book_seq = b.book_seq"
                              " and b.user_seq = ?";
        unique_ptr<PreparedStatement> stmnt(conn->prepareStatement(queryString));
        stmnt->setString(1, loginUserInfo->userId);
        ResultSet *res = stmnt->executeQuery();
        while (res->next()) {
            cout << "번호 : " << res->getInt("bookSeq") << endl;
            cout << "책이름 : " << res->getString("bookName") << endl;
            cout << "저자 : " << res->getString("bookAuth") << endl;
            cout << "대여상태 : " << res->getInt("bookStatus") << endl;
        }
    }catch(SQLException& e) {
        cerr << "Error (UserClass::selectCheckOutBookList) : " << e.what() << endl;
    }
}

bool UserClass::updateUserInfo(UserInfo udtInfo) {
    try {
        string queryString  = "update user "
                              "set user_tel = ?"
                              " , user_addr = ? "
                              "where user_id = ?";
        unique_ptr<PreparedStatement> stmnt(conn->prepareStatement(queryString));
        stmnt->setString(1, udtInfo.userTel);
        stmnt->setString(2, udtInfo.userAddress);
        stmnt->setString(3, udtInfo.userId);

        stmnt->executeQuery();
        return true;
    }catch(SQLException& e) {
        cerr << "Error (UserClass::updateUserInfo) : " << e.what() << endl;
        return false;
    }
}

string UserClass::searchUserId(UserInfo searchInfo) {
    try {
        string queryString  = "select user_id userId "
                              "from user "
                              "where user_name = ? "
                              "and user_tel = ?";
        unique_ptr<PreparedStatement> stmnt(conn->prepareStatement(queryString));
        stmnt->setString(1, searchInfo.userName);
        stmnt->setString(2, searchInfo.userTel);

        ResultSet *res = stmnt->executeQuery();
        res->next();
        if (res->getString("userId") != NULL) {
            cout << "회원가입된 아이디 : " << res->getString(1) << endl;
            return string(res->getString(1));
        }else {
            cout << "가입된 정보가 없습니다." << endl;
            return "";
        }

    }catch(SQLException& e) {
        cerr << "Error (UserClass::searchUserId) : " << e.what() << endl;
        return "";
    }
}

string UserClass::searchUserPassword(UserInfo searchInfo) {
    try {
        string queryString  = "select user_id userId "
                              "from user "
                              "where user_Id = ? "
                              "and user_name = ? "
                              "and user_tel = ?";
        unique_ptr<PreparedStatement> stmnt(conn->prepareStatement(queryString));
        stmnt->setString(1, searchInfo.userId);
        stmnt->setString(2, searchInfo.userName);
        stmnt->setString(3, searchInfo.userTel);

        ResultSet *res = stmnt->executeQuery();
        res->next();
        if (res->getString("userId") != NULL) {
            cout << searchInfo.userId << "의 비밀번호는 " << res->getString(1) << " 입니다." << endl;
            return string(res->getString(1));
        }else {
            cout << "가입된 정보가 없습니다." << endl;
            return "";
        }
    }catch (SQLException& e) {
        cerr << "Error (UserClass::searchUserPassword) : " << e.what() << endl;
        return "";
    }
}

bool UserClass::duplicateUserId(string id) {
    try {
        string queryString = "select count(1) cnt "
                             "from user "
                             "where user_id = ?";
        unique_ptr<PreparedStatement> stmnt(conn->prepareStatement(queryString));
        stmnt->setString(1, id);
        ResultSet *res = stmnt->executeQuery();
        res->next();
        if (res->getInt("cnt") > 0) {
            cout << "이미 존재하는 아이디입니다" << endl;
            return false;
        }else {
            cout << "사용가능한 아이디입니다." << endl;
            return true;
        }
    }catch(SQLException& e) {
        cerr << "Error (UserClass::duplicateUserId) : " << e.what() << endl;
        return false;
    }
}

void UserClass::selectUserList(int pageIdx) {
    try {
        int pageStartNum = (pageIdx - 1) * 10;
        int pageEndNum = pageIdx * 10;

        string queryString  = "select @ROWNUM:=@ROWNUM+1 AS ROWNUM"
                              ", A.* "
                              "from ("
                              "     select u.user_seq userSeq"
                              "      , u.user_name userName"
                              "      , u.user_tel userTel"
                              "      , count(b.seq) bookCnt"
                              "      , u.user_grade userGrade "
                              "     from user u "
                              "     left outer join book b "
                              "      on u.user_seq = b.user_seq "
                              "     group by 1, 2, 3, 5) A "
                              "     , (SELECT @ROWNUM:=0) R "
                              "     LIMIT ?, ?";

        unique_ptr<PreparedStatement> stmnt(conn->prepareStatement(queryString));
        stmnt->setInt(1, pageStartNum);
        stmnt->setInt(2, pageEndNum);
        ResultSet *res = stmnt->executeQuery();

        res->last();
        int totalRow = res->getRow();
        res->beforeFirst();

        if (totalRow != 0) {
            while (res->next()) {
                cout << "번호 : " << res->getString("ROWNUM") << endl;
                cout << "사용자 일련번호 : " << res->getString("userSeq") << endl;
                cout << "이름 : " << res->getString("userName") << endl;
                cout << "연락처 : " << res->getString("userTel") << endl;
                cout << "대여권수 : " << res->getString("bookCnt") << endl;
                cout << "회원등급 : " << res->getString("userGrade") << endl;
            }
        }else {
            cout << "조회된 내용이 없습니다." << endl;
        }
    }catch(SQLException& e) {
        cerr << "Error (UserClass::selectUserList) : " << e.what() << endl;
    }
}

void UserClass::deleteUserId(int userSeq) {
    try {
        string queryString  = "delete from user "
                              "where user_seq = ?";
        unique_ptr<PreparedStatement> stmnt(conn->prepareStatement(queryString));
        stmnt->setInt(1, userSeq);
        stmnt->executeQuery();
    }catch(SQLException& e) {
        cerr << "Error (UserClass::deleteUserId) : " << e.what() << endl;
    }
}

void UserClass::updateUserGrade(int grade, int userSeq) {
    try {
        string queryString  = "update user "
                              "set user_grade = ? "
                              "where user_seq = ?";
        unique_ptr<PreparedStatement> stmnt(conn->prepareStatement(queryString));
        stmnt->setInt(1, grade);
        stmnt->setInt(2, userSeq);
        stmnt->executeQuery();
    }catch(SQLException& e) {
        cerr << "Error (UserClass::updateUserGrade) : " << e.what() << endl;
    }
}


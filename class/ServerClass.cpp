#include "../header/ServerClass.h"

string ServerClass::serverHandler (string data){

    UserClass user;
    BookInfoClass book;

    string req = "";
    UserInfo userInfo;
    BookInfo bookInfo;

    UserInfo resultUserInfo;
    BookInfo resultBookInfo;
    int pageNum = 1;

    //클라이언트에게 받은 메세지 역직렬화
    rcevMsgConvert(&data, &req, &userInfo, &bookInfo, &pageNum);

    int reqNum = atoi(req.c_str());
    string response;
    string msg;

    switch (reqNum){
        case USER_LOGIN:
            if (user.login(userInfo.userId, userInfo.userPwd)) {
                response = "OK";
            }else {
                response = "ERROR";
            }
            break;
        case USER_LOGOUT:
            cout << "로그아웃" << endl;
            break;
        case USER_JOIN:
            if (user.join(userInfo)) {
                response = "OK";
            }else {
                response = "ERROR";
            }
            break;
        case USER_INFO:
            resultUserInfo = user.selectUserInfo(userInfo.userId);
            break;
        case SEARCH_USER_ID:
            resultUserInfo.userId = user.searchUserId(userInfo);
            break;
        case SEARCH_USER_PWD:
            resultUserInfo.userPwd = user.searchUserPassword(userInfo);
            break;
        case DUPLICATE_USER_ID:
            if (user.duplicateUserId(userInfo.userId)) {
                response = "OK";
            }else {
                response = "ERROR";
            }
            break;
        case USER_LIST:
            resultUserInfo = user.selectUserList(pageNum);
            cout << "userList는 잘 가지고 와써용" << endl;
            break;
        case DELETE_USER:
            if (user.deleteUserId(userInfo.userSeq)) {
                response = "OK";
            }else {
                response = "ERROR";
            }
            break;
        case UPDATE_USER:
            if (user.updateUserInfo(userInfo)) {
                response = "OK";
            }else {
                response = "ERROR";
            }
            break;
        case UPDATE_USER_GRADE:
            if (user.updateUserGrade(userInfo.userGrade, userInfo.userSeq)) {
                response = "OK";
            }else {
                response = "ERROR";
            }
            break;
        case BOOK_LIST:
            book.selectBookList(pageNum);
            break;
        case BOOK_INFO:
            book.selectBookInfo(bookInfo.bookSeq);
            break;
        case BOOK_CHECK_IN:
            book.checkIn(userInfo.userSeq, bookInfo.bookSeq);
            break;
        case BOOK_CHECK_OUT:
            book.checkIn(userInfo.userSeq, bookInfo.bookSeq);
            break;
        default:break;
    };
    response = "OK";
    msg = sendMsgConvert(req, response, &userInfo, &bookInfo);

    return msg;
}

void ServerClass::rcevMsgConvert(string* msg, string* req, UserInfo *user, BookInfo *book, int *pageIndex) {
    CommClass *comm = new CommClass();
    cout << "여기왔니?? : 서버" << endl;
    *req = comm->split(*msg, DATA_SPRT)[0];
    user->deserialize(comm->split(*msg, DATA_SPRT)[1]);
    book->deserialize(comm->split(*msg, DATA_SPRT)[2]);
    *pageIndex = atoi(comm->split(*msg, DATA_SPRT)[3].c_str());
    cout << "Server receive message deserialize Success!! " << endl;
}

string ServerClass::sendMsgConvert(string req, string reqSucc, UserInfo *user, BookInfo *book) {
    string msg = "";
    msg += req + DATA_SPRT;
    msg += reqSucc + DATA_SPRT;
    if (atoi(req.c_str()) == BOOK_LIST)
        msg += book->serializeList();
    else if (atoi(req.c_str()) == USER_LIST)
        msg += user->serializeList();
    else {
        msg += user->serialize() + DATA_SPRT;
        msg += book->serialize();
    }

    cout << "Server send message serialize Success!! " << endl;
    return msg;
}
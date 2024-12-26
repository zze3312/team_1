#include "../header/ClientClass.h"

string ClientClass::sendMsgConvert(string req, UserInfo *user, BookInfo *book, int pageIndex) {
    string resultData = "";

    resultData += req + DATA_SPRT;
    resultData += user->serialize() + DATA_SPRT;
    resultData += book->serialize() + DATA_SPRT;
    resultData += pageIndex;
    cout << "Client send message serialize Success!! " << endl;
    return resultData;
}

void ClientClass::receiveMsgConvert(string msg, UserInfo *user, BookInfo *book) {
    CommClass comm;
    cout << "여기왔니?? : 클라" << endl;
    int req;
    string response;
    req = atoi(comm.split(msg, DATA_SPRT)[0].c_str());
    response = comm.split(msg, DATA_SPRT)[1].c_str();

    if (response == "OK") {
        if (req == BOOK_LIST) {
            book->deserializeList(comm.split(msg, DATA_SPRT)[2]);
        }else if (req == USER_LIST) {
            user->deserializeList(comm.split(msg, DATA_SPRT)[2]);
        }else {
            user->deserialize(comm.split(msg, DATA_SPRT)[2]);
            book->deserialize(comm.split(msg, DATA_SPRT)[3]);
        }
    }
    cout << "Client receive message deserialize Success!! " << endl;
}
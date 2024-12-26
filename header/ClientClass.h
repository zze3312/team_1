#ifndef CLIENTCLASS_H
#define CLIENTCLASS_H
#include "DbClass.h"
#include "../header/ClientServerNum.h"

class ClientClass {
public:
    string sendMsgConvert(string req, UserInfo *user, BookInfo *book, int pageIndex);
    void receiveMsgConvert(string msg, UserInfo *user, BookInfo *book);
};



#endif //CLIENTCLASS_H

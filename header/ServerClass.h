#ifndef SERVERCLASS_H
#define SERVERCLASS_H
#include "ClientServerNum.h"
#include "UserClass.h"
#include "BookInfoClass.h"
#include "ServerClientClass.h"
#include "ServerClass.h"


class ServerClass {

public:
    string serverHandler(string data);
    void rcevMsgConvert(string *data, string* req, UserInfo *user, BookInfo *book, int *pageIndex);
    string sendMsgConvert(string req, string reqSucc, UserInfo *user, BookInfo *book);
};



#endif //SERVERCLASS_H

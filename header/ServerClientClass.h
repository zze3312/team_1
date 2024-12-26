//
// Created by lms on 24. 12. 25.
//

#ifndef SERVERCLIENTCLASS_H
#define SERVERCLIENTCLASS_H
#include <iostream>
#include <mariadb/conncpp.hpp>
#include <cstring>
#include <csignal>
#include <unistd.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include "ServerClass.h"
#include "ClientClass.h"


#define BUF_SIZE 10000

using namespace std;
void read_childproc(int sig);

class ServerClientClass {
    const string PORT_NUM = "10000";
    const string IP_ADDR = "127.0.0.1";
    int serv_sock = 0; // 서버소켓의 파일디스크립터 저장 공간
    void error_handling(const char *message);
public:
    void serverCheck();
    void serverOn(string port);
    void serverOff();
    void clientConnect(string port, string reqNum, UserInfo *user, BookInfo *book, int pageIndex);
};

#endif //SERVERCLIENTCLASS_H

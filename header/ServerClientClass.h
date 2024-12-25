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
#include "CommClass.h"

#define BUF_SIZE 1024

using namespace std;
CommClass comm;

void read_childproc(int sig);

class ServerClientClass {
    const string PORT_NUM = "10000";
    const string IP_ADDR = "127.0.0.1";
    int serv_sock = 0; // 서버소켓의 파일디스크립터 저장 공간
    void error_handling(char *message);
public:
    void serverCheck();
    void serverOn();
    void serverOff();
    void clientConnect();
};

struct test : public ServerClientClass{
    int a;
    string b;
    string c;
    test(){}
    test(int a,char *b,char *c) : a(a), b(b), c(c){}
    string serializeData(){
        return to_string(a) + "^%^" + b + "^%^" + c;
    }
    void deserializeData(string s){
        cout << "1 : " << comm.split(s, "^%^")[0] << endl;
        cout << "2 : " << comm.split(s, "^%^")[1] << endl;
        cout << "3 : " << comm.split(s, "^%^")[2] << endl;
    }
};

#endif //SERVERCLIENTCLASS_H

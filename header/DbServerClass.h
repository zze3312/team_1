#ifndef DATABASECLASS_H
#define DATABASECLASS_H

#include <iostream>
#include <mariadb/conncpp.hpp>
#include <cstring>
#include <sstream>
#include <vector>
#include <csignal>
#include <unistd.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#define BUF_SIZE 1024


using namespace std;
using namespace sql;

struct UserInfo {
    int userSeq;
    string userId;
    string userPwd;
    string userName;
    string userBirth;   // 19990101 형식으로 받기
    bool userGender;    // 0이면 남자 1이면 여자
    string userTel;     // 숫자만 입력
    string userAddress;
    int userGrade;
    string userJoinDate;
};
struct BookInfo {
    int bookSeq;
    string bookRoomName; // 책이 있는 장소명
    string bookSerialNum;
    string bookName;
    string bookAuthor;
    string bookPublisher;
    string bookPubYear;
    string bookCallNumber;
    int bookStatus;
    string bookStartDate;
    string bookEndDate;
};

struct serverRequest {
    int requestSeq;
    string requestId;
};
void read_childproc(int sig);
    const string PORT_NUM = "10000";
    const string IP_ADDR = "127.0.0.1";
class DbServerClass {
    void error_handling(char *message);
protected:
    Driver* driver;
    unique_ptr<Connection> conn;
public:
    void databaseConnect();
    void serverOn();
    void clientConnect();
    vector<string> split(const string& input, string delimiter);
};



#endif //DATABASECLASS_H

#ifndef DATABASECLASS_H
#define DATABASECLASS_H

#include <iostream>
#include <mariadb/conncpp.hpp>
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


class DbClass {

protected:
    Driver* driver;
    unique_ptr<Connection> conn;
public:
    DbClass();
    ~DbClass();
};



#endif //DATABASECLASS_H

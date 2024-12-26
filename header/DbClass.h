#ifndef DATABASECLASS_H
#define DATABASECLASS_H

#include <iostream>
#include <mariadb/conncpp.hpp>
#include "CommClass.h"
using namespace std;
using namespace sql;
#define SEPARATOR "^%^"
#define DATA_SPRT "^&^"
#define LIST_SPRT "^*^"

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
    int bookCnt;
    UserInfo *userList;

    UserInfo() {
        userSeq = 0;
        userId = "";
        userPwd = "";
        userName = "";
        userBirth = "";
        userGender = false;
        userTel = "";
        userAddress = "";
        userGrade = 0;
        userJoinDate = "";
        userList = NULL;
    }

    string serialize() {
        return
        to_string(userSeq) + SEPARATOR
        + userId + SEPARATOR
        + userPwd + SEPARATOR
        + userName + SEPARATOR
        + userBirth + SEPARATOR
        + to_string(userGender) + SEPARATOR
        + userTel + SEPARATOR
        + userAddress + SEPARATOR
        + to_string(userGrade) + SEPARATOR
        + userJoinDate + SEPARATOR
        + to_string(bookCnt) + SEPARATOR;
    }

    void deserialize(string s) {
        CommClass *comm = new CommClass;
        userSeq = atoi(comm->split(s, SEPARATOR)[0].c_str());
        userId = comm->split(s, SEPARATOR)[1];
        userPwd = comm->split(s, SEPARATOR)[2];
        userName = comm->split(s, SEPARATOR)[3];
        userBirth = comm->split(s, SEPARATOR)[4];
        userGender = atoi(comm->split(s, SEPARATOR)[5].c_str());
        userTel = comm->split(s, SEPARATOR)[6];
        userAddress = comm->split(s, SEPARATOR)[7];
        userGrade = atoi(comm->split(s, SEPARATOR)[8].c_str());
        userJoinDate = comm->split(s, SEPARATOR)[9];
        bookCnt = atoi(comm->split(s, SEPARATOR)[10].c_str());
        delete comm;
    }

    string serializeList() {
        string resultStr = "";

        for (int i = 0; i < 10; i++) {
            string temp = to_string(userList[i].userSeq) + SEPARATOR
                + userList[i].userId + SEPARATOR
                + userList[i].userPwd + SEPARATOR
                + userList[i].userName + SEPARATOR
                + userList[i].userBirth + SEPARATOR
                + to_string(userList[i].userGender) + SEPARATOR
                + userList[i].userTel + SEPARATOR
                + userList[i].userAddress + SEPARATOR
                + to_string(userList[i].userGrade) + SEPARATOR
                + userList[i].userJoinDate + SEPARATOR
                + to_string(bookCnt) + SEPARATOR;
            resultStr += temp;
        }

        return resultStr;
    }

    void deserializeList(string s) {
        CommClass *comm = new CommClass;
        for (int i = 0; i < 10; i++) {
            userList[i].userSeq = atoi(comm->split(comm->split(s, LIST_SPRT)[i], SEPARATOR)[0].c_str());
            userList[i].userId = comm->split(comm->split(s, LIST_SPRT)[i], SEPARATOR)[1];
            userList[i].userPwd = comm->split(comm->split(s, LIST_SPRT)[i], SEPARATOR)[2];
            userList[i].userName = comm->split(comm->split(s, LIST_SPRT)[i], SEPARATOR)[3];
            userList[i].userBirth = comm->split(comm->split(s, LIST_SPRT)[i], SEPARATOR)[4];
            userList[i].userGender = atoi(comm->split(comm->split(s, LIST_SPRT)[i], SEPARATOR)[5].c_str());
            userList[i].userTel = comm->split(comm->split(s, LIST_SPRT)[i], SEPARATOR)[6];
            userList[i].userAddress = comm->split(comm->split(s, LIST_SPRT)[i], SEPARATOR)[7];
            userList[i].userGrade = atoi(comm->split(comm->split(s, LIST_SPRT)[i], SEPARATOR)[8].c_str());
            userList[i].userJoinDate = comm->split(comm->split(s, LIST_SPRT)[i], SEPARATOR)[9];
            userList[i].bookCnt = atoi(comm->split(comm->split(s, LIST_SPRT)[i], SEPARATOR)[10].c_str());
        }
        delete comm;
    }
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
    BookInfo *bookList;

    BookInfo() {
        bookSeq = 0;
        bookRoomName = "";
        bookSerialNum = "";
        bookName = "";
        bookAuthor = "";
        bookPublisher = "";
        bookPubYear = "";
        bookCallNumber = "";
        bookStatus = 0;
        bookStartDate = "";
        bookEndDate = "";
        bookList = NULL;
    }

    string serialize() {
        return
        to_string(bookSeq) + SEPARATOR
        + bookRoomName + SEPARATOR
        + bookSerialNum + SEPARATOR
        + bookName + SEPARATOR
        + bookAuthor + SEPARATOR
        + bookPublisher + SEPARATOR
        + bookPubYear + SEPARATOR
        + bookCallNumber + SEPARATOR
        + to_string(bookStatus) + SEPARATOR
        + bookStartDate + SEPARATOR
        + bookEndDate + SEPARATOR;
    }

    void deserialize(string s) {
        CommClass *comm = new CommClass;
        bookSeq = atoi(comm->split(s, SEPARATOR)[0].c_str());
        bookRoomName = comm->split(s, SEPARATOR)[1];
        bookSerialNum = comm->split(s, SEPARATOR)[2];
        bookName = comm->split(s, SEPARATOR)[3];
        bookAuthor = comm->split(s, SEPARATOR)[4];
        bookPublisher = comm->split(s, SEPARATOR)[5];
        bookPubYear = comm->split(s, SEPARATOR)[6];
        bookCallNumber = comm->split(s, SEPARATOR)[7];
        bookStatus = atoi(comm->split(s, SEPARATOR)[8].c_str());
        bookStartDate = comm->split(s, SEPARATOR)[9];
        bookEndDate = comm->split(s, SEPARATOR)[10];
        delete comm;
    }

    string serializeList() {
        string resultStr = "";

        for (int i = 0; i < 10; i++) {
            string temp = to_string(bookList[i].bookSeq) + SEPARATOR
                + bookList[i].bookRoomName + SEPARATOR
                + bookList[i].bookSerialNum + SEPARATOR
                + bookList[i].bookName + SEPARATOR
                + bookList[i].bookAuthor + SEPARATOR
                + bookList[i].bookPublisher + SEPARATOR
                + bookList[i].bookPubYear + SEPARATOR
                + bookList[i].bookCallNumber + SEPARATOR
                + to_string(bookList[i].bookStatus) + SEPARATOR
                + bookList[i].bookStartDate + SEPARATOR
                + bookList[i].bookEndDate + SEPARATOR;
            resultStr += temp;
        }
        return resultStr;
    }

    void deserializeList(string s) {
        CommClass *comm = new CommClass;
        for (int i = 0; i < 10; i++) {
            bookList[i].bookSeq = atoi(comm->split(comm->split(s, LIST_SPRT)[i], SEPARATOR)[0].c_str());
            bookList[i].bookRoomName = comm->split(comm->split(s, LIST_SPRT)[i], SEPARATOR)[1];
            bookList[i].bookSerialNum = comm->split(comm->split(s, LIST_SPRT)[i], SEPARATOR)[2];
            bookList[i].bookName = comm->split(comm->split(s, LIST_SPRT)[i], SEPARATOR)[3];
            bookList[i].bookAuthor = comm->split(comm->split(s, LIST_SPRT)[i], SEPARATOR)[4];
            bookList[i].bookPublisher = comm->split(comm->split(s, LIST_SPRT)[i], SEPARATOR)[5];
            bookList[i].bookPubYear = comm->split(comm->split(s, LIST_SPRT)[i], SEPARATOR)[6];
            bookList[i].bookCallNumber = comm->split(comm->split(s, LIST_SPRT)[i], SEPARATOR)[7];
            bookList[i].bookStatus = atoi(comm->split(comm->split(s, LIST_SPRT)[i], SEPARATOR)[8].c_str());
            bookList[i].bookStartDate = comm->split(comm->split(s, LIST_SPRT)[i], SEPARATOR)[9];
            bookList[i].bookEndDate = comm->split(comm->split(s, LIST_SPRT)[i], SEPARATOR)[10];
        }
        delete comm;
    }
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

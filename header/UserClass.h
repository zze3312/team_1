#ifndef USERCLASS_H
#define USERCLASS_H

#include <iostream>
#include "DbClass.h"

class UserClass : public DbClass{
    UserInfo *loginUserInfo;
public:
    UserClass();
    ~UserClass();
    bool login(string id, string pwd);  // 로그인
    bool join(UserInfo info);           // 회원가입
    void selectUserInfo();              // 회원정보 조회
    void selectCheckOutBookList();      // 대여중인 도서 목록
    bool updateUserInfo(UserInfo info); // 회원정보 수정
    string searchUserId(UserInfo info);   // ID찾기
    string searchUserPassword(UserInfo info); // 비밀번호찾기
    bool duplicateUserId(string id);    // ID 중복체크

    //관리자
    void selectUserList(int pageIdx);   // 회원목록 조회
	void deleteUserId(int seq);         // 회원삭제
    void updateUserGrade(int grade, int seq); // 회원등급 변경

    //getter, setter
    void setUserInfo(UserInfo info) {
        this -> loginUserInfo -> userSeq = info.userSeq;
        this -> loginUserInfo -> userId = info.userId;
        this -> loginUserInfo -> userName = info.userName;
        this -> loginUserInfo -> userBirth = info.userBirth;
        this -> loginUserInfo -> userGender = info.userGender;
        this -> loginUserInfo -> userTel = info.userTel;
        this -> loginUserInfo -> userAddress = info.userAddress;
        this -> loginUserInfo -> userGrade = info.userGrade;
    }

    UserInfo getUserInfo() {
        UserInfo info;
        info.userSeq = this -> loginUserInfo -> userSeq;
        info.userId = this -> loginUserInfo -> userId;
        info.userName = this -> loginUserInfo -> userName;
        info.userBirth = this -> loginUserInfo -> userBirth;
        info.userGender = this -> loginUserInfo -> userGender;
        info.userTel = this -> loginUserInfo -> userTel;
        info.userAddress = this -> loginUserInfo -> userAddress;
        info.userGrade = this -> loginUserInfo -> userGrade;

        return info;
    }
};



#endif //USERCLASS_H

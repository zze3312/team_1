#ifndef USERCLASS_H
#define USERCLASS_H

#include <iostream>
#include "DbClass.h"

class UserClass : public DbClass{
public:
    bool login(string id, string pwd);  // 로그인
    bool join(UserInfo info);           // 회원가입
    UserInfo selectUserInfo(string userId);              // 회원정보 조회
    BookInfo selectCheckOutBookList(string userId);      // 대여중인 도서 목록
    bool updateUserInfo(UserInfo info); // 회원정보 수정
    string searchUserId(UserInfo info);   // ID찾기
    string searchUserPassword(UserInfo info); // 비밀번호찾기
    bool duplicateUserId(string id);    // ID 중복체크

    //관리자
    UserInfo selectUserList(int pageIdx);   // 회원목록 조회
	bool deleteUserId(int seq);         // 회원삭제
    bool updateUserGrade(int grade, int seq); // 회원등급 변경
};



#endif //USERCLASS_H

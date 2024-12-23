#ifndef USERCLASS_H
#define USERCLASS_H

#include <iostream>
#include "DbServerClass.h"

class UserClass : public DbServerClass{
public:
    void login(string id, string pwd); // 로그인
    /*void join(); // 회원가입
    void selectUserInfo(); // 회원정보 조회
    void selectCheckOutBookList(); // 대여중인 도서 목록
    void updateUserInfo(); // 회원정보 수정
    void searchUserId(); // ID찾기
    void searchUserPassword(); // 비밀번호찾기
    void duplicateUserId(); // ID 중복체크

    //관리자
    void selectUserList(); // 회원목록 조회
	void deleteUserId(); // 회원삭제
    void updateUserGrade(); //회원등급 변경*/
};



#endif //USERCLASS_H

#ifndef CLIENTSERVERNUM_H
#define CLIENTSERVERNUM_H

enum {
    USER_LOGIN,             // 로그인
    USER_LOGOUT,            // 로그아웃
    USER_JOIN,              // 회원가입
    USER_INFO,              // 회원정보
    SEARCH_USER_ID,         // 아이디 찾기
    SEARCH_USER_PWD,        // 비밀번호 찾기
    DUPLICATE_USER_ID,      // ID중복체크
    USER_LIST,              // 회원목록
    DELETE_USER,            // 회원탈퇴
    UPDATE_USER,            // 회원정보 수정
    UPDATE_USER_GRADE,      // 회원등급 수정
    BOOK_LIST,              // 도서목록
    BOOK_INFO,              // 도서정보
    BOOK_CHECK_IN,          // 도서반납
    BOOK_CHECK_OUT          // 도서대여
};

#endif //CLIENTSERVERNUM_H

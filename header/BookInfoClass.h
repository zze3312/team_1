#ifndef BOOKINFOCLASS_H
#define BOOKINFOCLASS_H

#include <iostream>
#include "DbServerClass.h"
#include "UserClass.h"

class BookInfoClass : public DbClass{
public:
    void selectBookList(int pageIdx); // 도서 목록
    void selectBookInfo(int seq); // 도서 정보
    void checkOut(int useq, int bseq); // 대여하기
    void checkIn(int useq, int bseq); // 반납하기
};

#endif //BOOKINFOCLASS_H

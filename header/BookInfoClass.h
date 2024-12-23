#ifndef BOOKINFOCLASS_H
#define BOOKINFOCLASS_H

#include <iostream>
#include "DbServerClass.h"

class BookInfoClass : public DbServerClass{
public:
    void selectBookList(); // 도서 목록
    void selectBookInfo(); // 도서 정보
    void checkOut(); // 대여하기
    void checkIn(); // 반납하기
};



#endif //BOOKINFOCLASS_H

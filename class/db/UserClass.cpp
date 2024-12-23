#include "../../header/UserClass.h"

void UserClass::login(string userId, string userPassword){
    try {
        // createStaemet 객체 생성
        unique_ptr<PreparedStatement>  stmnt(conn->prepareStatement("select count(1) from user where id = ? and password = ?"));
        stmnt->setString(1, userId);
        stmnt->setString(2, userPassword);

        // 쿼리를 실행
        sql::ResultSet *res = stmnt->executeQuery();;
        res->next();
        int userCnt = res->getInt(1);
        if(userCnt > 0){
            cout << "로그인 성공!" << endl;
        }else{
            cout << "아이디나 패스워드가 잘못되었습니다." << endl;
        }

        // 실패시 오류 메세지 반환
    } catch(sql::SQLException& e){
        std::cerr << "Error selecting tasks: " << e.what() << std::endl;
    }
}
#include "../header/DbClass.h"

DbClass::DbClass() {
    try {
        // DB연결 객체 생성
        driver = mariadb::get_driver_instance();
        // 연결할 DB의 특정 IP, DB를 정의
        SQLString url("jdbc:mariadb://localhost:3306/project");
        // 연결할 DB를 사용할 유저를 정의
        Properties properties({{"user", "jh2"}, {"password", "admin"}});
        // 객체에 값을 통하여 연결을 시도
        conn = unique_ptr<Connection>(driver->connect(url, properties));
    }catch(SQLException& e) {
        cerr << "Error Connecting to MariaDB Platform: " << e.what() << endl;
        // 프로그램 비정상 종료
        exit(1);
    }
}

DbClass::~DbClass() {
    conn->close();
}
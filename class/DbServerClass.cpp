#include "../header/DbServerClass.h"

void DbServerClass::databaseConnect() {
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

void DbServerClass::serverOn() {
    int serv_sock;
    int clnt_sock;
    int clnt_addr_size;
    sockaddr_in serv_addr;
    sockaddr_in clnt_addr;

    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if (serv_sock == -1) {
        cerr << "Socket creation failed." << endl;
    }
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(10000);
    if (bind(serv_sock, (sockaddr *)&serv_addr, sizeof(serv_addr)) == -1) {
        cerr << "Bind failed." << endl;
    }
    if (listen(serv_sock, 5) == -1) {
        cerr << "Listen failed." << endl;
    }

    clnt_sock = accept(serv_sock, (sockaddr *)&clnt_addr, (socklen_t *)&clnt_addr_size);
    if (clnt_sock == -1) {
        cerr << "Accept failed." << endl;
    }

    serverRequest servReq;
    if (read(clnt_sock, &servReq, sizeof(servReq)) == -1) {
        cerr << "Read failed." << endl;
    }

    cout << "serverRequest : " << servReq.requestSeq << endl;

}


#include "../header/ServerClientClass.h"

void ServerClientClass::serverCheck(){
    if(serv_sock <= 0){
        cout << "서버닫혀있음" << endl;
    }
}

void ServerClientClass::serverOn(string port) {
    int clnt_sock; // 클라이언트소켓의 파일디스크립터 저장 공간
    int str_len, state;

    sockaddr_in serv_addr; // 서버의 소켓 주소 정보 - IPv4형식
    sockaddr_in clnt_addr; // 클라이언트의 소켓 주소 정보
    socklen_t clnt_addr_size; // 클라이언트 소켓의 길이 정보

    pid_t pid;
    struct sigaction act;

    act.sa_handler = read_childproc;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    sigaction(SIGCHLD, &act, NULL);

    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if (serv_sock == -1) {
        error_handling("socket() error");
    }
    cout << "서버시작..." << endl;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(port.c_str()));

    if (bind(serv_sock, (sockaddr*)&serv_addr, sizeof(serv_addr)) == -1) {
        error_handling("bind() error");
    }
    cout << "바인딩 완료..." << endl;
    if (listen(serv_sock, 5) == -1) {
        error_handling("listen() error");
    }
    cout << "리스닝 준비 완료..." << endl;

    while (1) {
        clnt_addr_size = sizeof(clnt_addr);
        clnt_sock = accept(serv_sock, (sockaddr*)&clnt_addr, &clnt_addr_size);
        if (clnt_sock == -1) {
            continue;
        }else {
            cout << "Client connected! > conn IP : " << inet_ntoa(clnt_addr.sin_addr) << endl;
        }
        pid = fork();
        if (pid == -1) {
            close(clnt_sock);
            continue;
        }
        if (pid == 0) {
            char clntMsg[BUF_SIZE] = "";
            close(serv_sock);
            cout << "클라이언트의 데이터 기다리는중..." << endl;
            //서버통신
            read(clnt_sock, &clntMsg, BUF_SIZE);
            cout << "클라이언트에게 데이터 받음 : " << clntMsg << endl;

            string reqMsg = clntMsg;
            string responseMsg = "";

            ServerClass *svr = new ServerClass();
            responseMsg = svr->serverHandler(reqMsg);
            cout << "요청 결과 : " << responseMsg << endl;


            // if (!strcmp(reqNum, "q\n") || !strcmp(reqNum, "Q\n")) {
            //     break;
            // }

            write(clnt_sock, responseMsg.c_str(), responseMsg.size());
            cout << "클라이언트에게 데이터 보냄 : " << responseMsg << endl;
            shutdown(clnt_sock, SHUT_WR);
            delete svr;
        }else {
            close(clnt_sock);
        }
    }
}

void ServerClientClass::serverOff() {
    close(serv_sock);
    cout << "서버 끝!" << endl;
}

void ServerClientClass::clientConnect(string port, string req, UserInfo *user, BookInfo *book, int pageIndex) {
    int sock;
    sockaddr_in serv_addr;

    int str_len = 0;
    int idx = 0;
    int read_len = 0;

    sock = socket(PF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        error_handling("socket() error");
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(IP_ADDR.c_str());
    serv_addr.sin_port = htons(atoi(port.c_str()));

    if (connect(sock, (sockaddr *)&serv_addr, sizeof(serv_addr)) == -1) {
        error_handling("connect() error");
    }
    cout << "클라이언트 커넥트 완료..." << endl;
    if (req == "q" || req == "Q") {
        return;
    }

    char reqMsg[BUF_SIZE];
    ClientClass *clnt_class = new ClientClass();
    strcpy(reqMsg, clnt_class->sendMsgConvert(req, user, book, pageIndex).c_str());

    write(sock, &reqMsg, sizeof(reqMsg));
    cout << "메세지 보냄!! : " << reqMsg << endl;

    char msg[BUF_SIZE] = "";
    read(sock, &msg, BUF_SIZE);

    printf("Message from server : %s\n", msg);
    cout << "메세지 받음!!" << endl;

    UserInfo t;
    t.deserialize(msg);

    shutdown(sock, SHUT_RD);
    close(sock);
    cout << "클라이언트 끝!" << endl;
}



void ServerClientClass::error_handling(const char *message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

void read_childproc(int sig) {
    pid_t pid;
    int status;
    pid = waitpid(-1, &status, WNOHANG);
    cout << "remove proc id : " << pid << endl;
}
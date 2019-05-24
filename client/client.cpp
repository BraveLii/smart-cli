#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include "common.h"

int main(int argc, const char** argv) {
    int sock_fd = -1;
    int ret = -1;
    sockaddr_in server_addr;

    char send_buf[MAX_BUF_LEN] = {0};
    char recv_buf[MAX_BUF_LEN] = {0};
    std::cout << HEAD_NAME;
    while(std::cin.getline(send_buf, MAX_BUF_LEN)){
        sock_fd = socket(AF_INET, SOCK_STREAM, 0);
        if(sock_fd == -1){
            std::cout << "create socket error !" << std::endl;
        }
        
        memset(&server_addr, 0x0, sizeof(server_addr));
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(SIN_PORT);
        server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
        ret = connect(sock_fd, (sockaddr*)&server_addr, sizeof(server_addr));
        if(ret == -1){
            std::cout << "connect error !" << std::endl;
        }
        
        write(sock_fd, send_buf, strlen(send_buf) + 1);
        std::cout << "send : " << send_buf << std::endl;
        int len = read(sock_fd, recv_buf, MAX_BUF_LEN);
        if(len > 0){
            
            len = 0;
            std::cout << recv_buf << std::endl;
        }

        memset(send_buf, 0x0, MAX_BUF_LEN);
        memset(recv_buf, 0x0, MAX_BUF_LEN);
        close(sock_fd);

        std::cout << std::endl;
        std::cout << HEAD_NAME;
        
    }

    close(sock_fd);

    return 0;
}
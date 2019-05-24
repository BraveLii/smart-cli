#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <thread>
#include "common.h"

int main(int argc, const char** argv) {
    struct sockaddr_in server_addr;
    int sock_fd = 0;

    memset(&server_addr, 0x0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SIN_PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(sock_fd == -1){
        std::cout << "create socket error !" << std::endl;
        return -1;
    }

    bind(sock_fd, (sockaddr*)&server_addr, sizeof(server_addr));
    listen(sock_fd, MAX_CONNECTION);

    while(1){
        struct sockaddr_in client_addr;
        socklen_t addr_len = sizeof(client_addr);

        int accept_fd = accept(sock_fd, (sockaddr*)&client_addr, &addr_len);
        if(accept_fd == -1){
            std::cout << "accept error !" << std::endl;
        }
        else{
            std::cout << "accept_fd [" << accept_fd << "] : "  << std::endl;
            auto  *p_thread = new std::thread(thread_func, std::ref(accept_fd));
            p_thread->detach();
        }
    }

    close(sock_fd);
    
    return 0;
}

void process(){
    sleep(10);
}

void thread_func(int sock_fd){
    char recv_buf[MAX_BUF_LEN] = {0};
    int len = read(sock_fd, recv_buf, MAX_BUF_LEN);
    if(len > 0){
        std::cout << "read from [" << sock_fd << "] : " << recv_buf << std::endl;
    }else{
        std::cout << "read 0" << std::endl; 
    }

    process();

    char send_buf[MAX_BUF_LEN] = {0};
    sprintf(send_buf, "you are %d !\n", sock_fd);
    write(sock_fd, send_buf, MAX_BUF_LEN);

    close(sock_fd);
}
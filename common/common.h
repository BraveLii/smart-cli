#pragma once

#define SIN_PORT 50001
#define MAX_CONNECTION 100
#define MAX_BUF_LEN 1024
#define HEAD_NAME "smart-cli >>"

void process();
void thread_func(int sock_fd);
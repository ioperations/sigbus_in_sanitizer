// 用sanitizer编译和不用sanitizer编译
// 本文件在低版本的编译器上可能不会输出这一行

// gcc7.3的时候sanitizer会抢占信号SIGBUS然后直接退出
// 在高版本的编译器上不管用不用sanitizer都会输出这一行

#include <unistd.h>

#include <csignal>
#include <iostream>

static void SigbusHandler(int signal) {
    if (signal == SIGBUS) {
        std::cout << "输出一行表示我们已经接受到了SIGBUS信号" << std::endl;
    }
    exit(0);
}

int main(int argc, char* argv[]) {
    pid_t pid = getpid();
    signal(SIGBUS, SigbusHandler);
    kill(pid, SIGBUS);
    return 0;
}

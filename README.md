# Poke

# -编译<br>
  ~$ g++ main.cpp httpsocket.cpp -o Poke <br>
  (if you use up failed, please try this command: g++ main.cpp httpsocket.cpp -o Poke -std=c++11 -lpthread)
  
# c++头文件<br>
#include <iostream><br>
#include <sstream><br>
#include <fstream><br>
#include <cassert><br>
#include <cstdio><br>
#include <string><br>
#include <string.h><br>
#include <stdio.h><br>
#include <stdlib.h><br>
#include <dirent.h><br>
#include <unistd.h><br>
#include <pthread.h><br>
#include <netdb.h><br>
#include <fcntl.h><br>
#include <errno.h><br>
#include <termios.h><br>
#include <arpa/inet.h><br>
#include <netinet/in.h><br>
#include <sys/select.h><br>
#include <sys/stat.h><br>
#include <sys/types.h><br>
#include <sys/socket.h><br>


# 网络功能<br>
  17.11.11-废除系统命令"wget"-更新为Linux Socket连接<br>

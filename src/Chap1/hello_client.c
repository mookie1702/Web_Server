#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

void error_handling(char *message);

int main(int argc, char **argv) {
  int sock;
  struct sockaddr_in serv_addr;
  int str_len;
  char message[30];

  if (3 != argc) {
    printf("Usage : %s <IP> <port> \n", argv[0]);
    exit(1);
  }
  // 创建客户端套接字
  if (-1 == (sock = socket(PF_INET, SOCK_STREAM, 0)))
    error_handling("socket() error!");
  // 设置服务器地址和接口
  memset(&serv_addr, 0, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
  serv_addr.sin_port = htons(atoi(argv[2]));
  // 连接服务器
  if (-1 == (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr))))
    error_handling("connect() error!");
  // 接收数据
  str_len = read(sock, message, sizeof(message) - 1);
  if (-1 == str_len) error_handling("read() error!");
  printf("Message from server : %s \n", message);
  close(sock);
  return 0;
}

void error_handling(char *message) {
  fputs(message, stderr);
  fputc('\n', stderr);
  exit(1);
}

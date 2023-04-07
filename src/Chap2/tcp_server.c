#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

// 异常处理函数
void error_handling(char *message);

int main(int argc, char **argv) {
  // 定义服务器套接字和客户端套接字
  int serv_sock, clnt_sock;
  // 定义服务器地址和客户端地址
  struct sockaddr_in serv_addr;
  struct sockaddr_in clnt_addr;
  socklen_t clnt_addr_size;
  // 准备发送的消息
  char message[] = "Hello, world!";
  // 异常处理
  if (argc != 2) {
    printf("Usage: %s <port>\n", argv[0]);
    exit(1);
  }
  // 创建套接字
  if (-1 == (serv_sock = socket(PF_INET, SOCK_STREAM, 0)))
    error_handling("socket() error!");
  // 设置服务器套接字地址
  memset(&serv_addr, 0, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  serv_addr.sin_port = htons(atoi(argv[1]));
  // 将服务器套接字绑定IP和PORT
  if (-1 == (bind(serv_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr))))
    error_handling("bind() error!");
  // 监听服务器套接字
  if (-1 == listen(serv_sock, 5)) error_handling("listen() error!");
  // 接受客户端里连接
  clnt_addr_size = sizeof(clnt_addr);
  clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_addr, &clnt_addr_size);
  if (-1 == clnt_sock) error_handling("accept() error!");
  // 向客户端套接字发送消息
  write(clnt_sock, message, sizeof(message));
  close(clnt_sock);
  close(serv_sock);
  return 0;
}

void error_handling(char *message) {
  fputs(message, stderr);
  fputc('\n', stderr);
  exit(1);
}

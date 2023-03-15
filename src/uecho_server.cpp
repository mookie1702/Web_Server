#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 30

void error_handling(char *message);

int main(int argc, char **argv) {
  char message[BUF_SIZE];
  int str_len;

  int serv_sock, clnt_sock;
  struct sockaddr_in serv_addr, clnt_addr;
  socklen_t clnt_addr_size;

  if (argc != 2) {
    printf("Usage: %s <port>\n", argv[0]);
    exit(1);
  }

  if (-1 == (serv_sock = socket(PF_INET, SOCK_DGRAM, 0))) {
    error_handling("socket() error!");
  }

  memset(&serv_addr, 0, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  serv_addr.sin_port = htons(atoi(argv[1]));

  if (-1 ==
      (bind(serv_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)))) {
    error_handling("bind() error!");
  }

  while (1) {
    clnt_addr_size = sizeof(clnt_addr);
    str_len = recvfrom(serv_sock, message, BUF_SIZE, 0,
                       (struct sockaddr *)&clnt_addr, &clnt_addr_size);
    sendto(serv_sock, message, BUF_SIZE, 0, (struct sockaddr *)&clnt_addr,
           clnt_addr_size);
  }
  close(serv_sock);
  return 0;
}

void error_handling(char *message) {
  fputs(message, stderr);
  fputc('\n', stderr);
  exit(1);
}

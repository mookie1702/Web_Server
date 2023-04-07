#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024
#define OPSZ 4

void error_handling(char *message);
int calculate(int opnum, int opnds[], char op);

int main(int argc, char **argv) {
  char opinfo[BUF_SIZE];
  int result, count, recv_cnt, recv_len;
  char op;

  int serv_sock, clnt_sock;
  struct sockaddr_in serv_addr, clnt_addr;
  socklen_t clnt_addr_size;

  if (argc != 2) {
    printf("Usage: %s <port>\n", argv[0]);
    exit(1);
  }

  if (-1 == (serv_sock = socket(PF_INET, SOCK_STREAM, 0)))
    error_handling("socket() error!");

  memset(&serv_addr, 0, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  serv_addr.sin_port = htons(atoi(argv[1]));

  if (-1 == (bind(serv_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr))))
    error_handling("bind() error!");
  if (-1 == listen(serv_sock, 5)) error_handling("listen() error!");

  clnt_addr_size = sizeof(clnt_addr);
  
  for (int i = 0; i < 5; i++) {
    clnt_sock =
        accept(serv_sock, (struct sockaddr *)&clnt_addr, &clnt_addr_size);
    if (-1 == clnt_sock) {
      error_handling("accept() error!");
    } else {
      printf("Connected client %d \n", i + 1);
    }

    count = 0;
    read(clnt_sock, &count, 1);

    recv_len = 0;
    while ((count * OPSZ + 1) > recv_len) {
      recv_cnt = read(clnt_sock, &opinfo[recv_len], BUF_SIZE - 1);
      recv_len += recv_cnt;
    }
    result = calculate(count, (int *)opinfo, opinfo[recv_len - 1]);
    write(clnt_sock, (char *)&result, sizeof(result));
    close(clnt_sock);
  }
  close(serv_sock);

  return 0;
}

int calculate(int opnum, int opnds[], char op) {
  int result = opnds[0], i;
  switch (op) {
    case '+':
      for (i = 1; i < opnum; i++) result += opnds[i];
      break;
    case '-':
      for (i = 1; i < opnum; i++) result -= opnds[i];
      break;
    case '*':
      for (i = 1; i < opnum; i++) result *= opnds[i];
      break;
  }
  return result;
}

void error_handling(char *message) {
  fputs(message, stderr);
  fputc('\n', stderr);
  exit(1);
}

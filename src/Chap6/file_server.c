#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 30

void error_handling(char *message);

int main(int argc, char **argv) {
  int serv_sock, clnt_sock;
  struct sockaddr_in serv_addr, clnt_addr;
  socklen_t clnt_addr_size;

  FILE *fp;
  int read_cnt;
  char message[BUF_SIZE];

  if (argc != 2) {
    printf("Usage: %s <port>\n", argv[0]);
    exit(1);
  }

  fp = fopen("file_server.c", "rb");

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
  clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_addr, &clnt_addr_size);

  while (1) {
    read_cnt = fread((void *)message, 1, BUF_SIZE, fp);
    if (read_cnt < BUF_SIZE) {
      write(clnt_sock, message, read_cnt);
      break;
    }
    write(clnt_sock, message, BUF_SIZE);
  }

  shutdown(clnt_sock, SHUT_WR);
  read(clnt_sock, message, BUF_SIZE);
  printf("Message from client: %s \n", message);

  fclose(fp);
  close(clnt_sock);
  close(serv_sock);
  return 0;
}

void error_handling(char *message) {
  fputs(message, stderr);
  fputc('\n', stderr);
  exit(1);
}

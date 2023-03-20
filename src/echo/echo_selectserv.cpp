#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <sys/select.h>

#define BUF_SIZE 100

void error_handling(char *message);

int main(int argc, char **argv) {
  int serv_sock, clnt_sock;
  struct sockaddr_in serv_addr, clnt_addr;
  socklen_t clnt_addr_size;

  fd_set reads, cpy_reads;
  struct timeval timeout;
  int fd_max, str_len, fd_num;

  char message[BUF_SIZE];

  if (argc != 2) {
    printf("Usage: %s <port>\n", argv[0]);
    exit(1);
  }

  if (-1 == (serv_sock = socket(PF_INET, SOCK_STREAM, 0))) {
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
  if (-1 == listen(serv_sock, 5)) {
    error_handling("listen() error!");
  }

  FD_ZERO(&reads);
  FD_SET(serv_sock, &reads);
  fd_max = serv_sock;

  while (1) {
    cpy_reads = reads;
    timeout.tv_sec = 5;
    timeout.tv_usec = 5000;

    if (-1 == (fd_num = select(fd_max + 1, &cpy_reads, 0, 0, &timeout))) {
      break;
    }
    if (0 == fd_num) {
      continue;
    }

    for (int i = 0; i < fd_max + 1; i++) {
      if (FD_ISSET(i, &cpy_reads)) {
        // connection request!
        if (i == serv_sock) {
          clnt_addr_size = sizeof(clnt_addr);
          clnt_sock =
              accept(serv_sock, (struct sockaddr *)&clnt_addr, &clnt_addr_size);
          FD_SET(clnt_sock, &reads);
          if (fd_max < clnt_sock) fd_max = clnt_sock;
          printf("connected client: %d \n", clnt_sock);
        } else {
          str_len = read(i, message, BUF_SIZE);
          if (0 == str_len) {
            FD_CLR(i, &reads);
            close(i);
            printf("closed client: %d \n", i);
          } else {
            write(i, message, str_len);
          }
        }
      }
    }
  }
  close(serv_sock);
  return 0;
}

void error_handling(char *message) {
  fputs(message, stderr);
  fputc('\n', stderr);
  exit(1);
}

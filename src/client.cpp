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
  char message[30];
  int str_len;

  if (3 != argc) {
    printf("Usage : %s <IP> <port> \n", argv[0]);
    exit(1);
  }

  if (-1 == (sock = socket(PF_INET, SOCK_STREAM, 0))) {
    char error_message[] = "socket() error!";
    error_handling(error_message);
  }

  memset(&serv_addr, 0, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
  serv_addr.sin_port = htons(atoi(argv[2]));

  if (-1 == (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)))) {
    char error_message[] = "connect() error!";
    error_handling(error_message);
  }

  str_len = read(sock, message, sizeof(message) - 1);
  if (-1 == str_len) {
    char error_message[] = "read() error!";
    error_handling(error_message);
  }

  printf("Message from server : %s \n", message);
  close(sock);
  return 0;
}

void error_handling(char *message) {
  fputs(message, stderr);
  fputc('\n', stderr);
  exit(1);
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 30

void error_handling(char *message);

int main(int argc, char **argv) {
  int sock;
  struct sockaddr_in serv_addr;

  FILE *fp;
  int recv_cnt;
  char message[BUF_SIZE];

  if (3 != argc) {
    printf("Usage : %s <IP> <port> \n", argv[0]);
    exit(1);
  }

  fp = fopen("receive.dat", "wb");

  if (-1 == (sock = socket(PF_INET, SOCK_STREAM, 0)))
    error_handling("socket() error!");

  memset(&serv_addr, 0, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
  serv_addr.sin_port = htons(atoi(argv[2]));

  if (-1 == (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)))) {
    error_handling("connect() error!");
  } else {
    puts("Connected........");
  }

  while (0 != (recv_cnt = read(sock, message, BUF_SIZE))) {
    fwrite((void *)message, 1, recv_cnt, fp);
  }
  puts("Receive file data");
  write(sock, "Thank you", 10);
  fclose(fp);
  close(sock);
  return 0;
}

void error_handling(char *message) {
  fputs(message, stderr);
  fputc('\n', stderr);
  exit(1);
}

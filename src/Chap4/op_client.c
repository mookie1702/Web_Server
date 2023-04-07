#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024
#define RLT_SIZE 4
#define OPSZ 4

void error_handling(char *message);

int main(int argc, char **argv) {
  int count, result;
  char opmsg[BUF_SIZE];
  int sock;
  struct sockaddr_in serv_addr;

  if (3 != argc) {
    printf("Usage : %s <IP> <port> \n", argv[0]);
    exit(1);
  }

  if (-1 == (sock = socket(PF_INET, SOCK_STREAM, 0)))
    error_handling("socket() error!");

  memset(&serv_addr, 0, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
  serv_addr.sin_port = htons(atoi(argv[2]));
  if (-1 == (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr))))
    error_handling("connect() error!");
  else
    puts("Connected........");

  fputs("Operand count: ", stdout);
  scanf("%d", &count);
  opmsg[0] = (char)count;

  for (int i = 0; i < count; i++) {
    printf("Operand %d: ", i + 1);
    scanf("%d", (int *)&opmsg[i * OPSZ + 1]);
  }
  fgetc(stdin);
  fputs("Operator:", stdout);

  scanf("%c", &opmsg[count * OPSZ + 1]);
  write(sock, opmsg, count * OPSZ + 2);

  read(sock, &result, RLT_SIZE);
  printf("Operation result: %d\n", result);

  close(sock);
  return 0;
}

void error_handling(char *message) {
  fputs(message, stderr);
  fputc('\n', stderr);
  exit(1);
}

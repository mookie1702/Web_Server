#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <sys/socket.h>

#define BUF_SIZE 30

void error_handling(char *message);
void read_childproc(int sig);

int main(int argc, char **argv) {
  int serv_sock, clnt_sock;
  struct sockaddr_in serv_addr, clnt_addr;
  socklen_t clnt_addr_size;

  int state;
  pid_t pid;
  struct sigaction act;

  char message[BUF_SIZE];
  int str_len;

  if (argc != 2) {
    printf("Usage: %s <port>\n", argv[0]);
    exit(1);
  }

  act.sa_handler = read_childproc;
  sigemptyset(&act.sa_mask);
  act.sa_flags = 0;
  state = sigaction(SIGCHLD, &act, 0);

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

  while (1) {
    clnt_addr_size = sizeof(clnt_addr);
    clnt_sock =
        accept(serv_sock, (struct sockaddr *)&clnt_addr, &clnt_addr_size);
    if (-1 == clnt_sock) {
      continue;
    } else {
      printf("New client Connected...\n");
    }

    pid = fork();
    if (-1 == pid) {
      close(clnt_sock);
      continue;
    }
    if (0 == pid) {
      close(serv_sock);
      while (0 != (str_len = read(clnt_sock, message, BUF_SIZE))) {
        write(clnt_sock, message, str_len);
      }
      close(clnt_sock);
      puts("Client disconnected...");
      return 0;
    } else {
      close(clnt_sock);
    }

    close(clnt_sock);
  }
  close(serv_sock);

  return 0;
}

void read_childproc(int sig) {
  pid_t pid;
  int status;
  pid = waitpid(-1, &status, WNOHANG);
  printf("removed proc id: %d \n", pid);
}

void error_handling(char *message) {
  fputs(message, stderr);
  fputc('\n', stderr);
  exit(1);
}

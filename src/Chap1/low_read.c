#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUF_SIZE 30

void error_handling(char *message);

int main(int argc, char **argv) {
  int fd;
  char buf[BUF_SIZE];

  fd = open("data.txt", O_RDONLY);
  if (-1 == fd) error_handling("open() error!");
  printf("file descriptor: %d \n", fd);

  if (-1 == read(fd, buf, sizeof(buf))) error_handling("write() error!");
  printf("file data: %s", buf);
  close(fd);
  return 0;
}

void error_handling(char *message) {
  fputs(message, stderr);
  fputc('\n', stderr);
  exit(1);
}

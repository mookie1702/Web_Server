#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

using namespace std;

#define BUF_SIZE 30

void error_handling(string message);

int main(int argc, char** argv) {
  int recv_sock;
  int str_len;
  char buf[BUF_SIZE];

  return 0;
}

void error_handling(string message) {
  cout << message << endl;
  exit(1);
}

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
  struct sockaddr_in adr;
  struct ip_mreq join_adr;

  int str_len;
  char buf[BUF_SIZE];

  if (3 != argc) {
    cout << "Usage: " << argv[0] << " <GroupIP> <PORT>" << endl;
    exit(1);
  }

  recv_sock = socket(PF_INET, SOCK_DGRAM, 0);
  memset(&adr, 0, sizeof(adr));
  adr.sin_family = AF_INET;
  adr.sin_addr.s_addr = htonl(INADDR_ANY);
  adr.sin_port = htons(atoi(argv[2]));

  if (-1 == bind(recv_sock, (struct sockaddr*)&adr, sizeof(adr)))
    error_handling("bind() error!");

  join_adr.imr_multiaddr.s_addr = inet_addr(argv[1]);
  join_adr.imr_interface.s_addr = htonl(INADDR_ANY);

  setsockopt(recv_sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, (void*)&join_adr,
             sizeof(join_adr));

  while (1) {
    str_len = recvfrom(recv_sock, buf, BUF_SIZE - 1, 0, NULL, 0);
    if (0 > str_len) break;
    buf[str_len] = 0;
    fputs(buf, stdout);
  }

  close(recv_sock);
  return 0;
}

void error_handling(string message) {
  cout << message << endl;
  exit(1);
}

#include <iostream>
#include <string>
#include <sstream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include "rapidjson/document.h"

int main() {
  const char *host = "localhost";
  const char *port = "12345";  // 服务器监听的端口号

  // 创建 socket
  struct addrinfo hints, *res;
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  getaddrinfo(host, port, &hints, &res);
  int sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

  // 连接服务器
  connect(sockfd, res->ai_addr, res->ai_addrlen);

  // 接收数据
  char buffer[4096];
  int bytes_received = recv(sockfd, buffer, sizeof(buffer), 0);
  std::string data(buffer, bytes_received);

  // 解析 JSON
  rapidjson::Document doc;
  doc.Parse(data.c_str());
  if (doc.HasParseError()) {
    std::cerr << "JSON parse error: " << doc.GetParseError() << std::endl;
    return 1;
  }

  // 处理 JSON 数据
  if (doc.HasMember("name") && doc["name"].IsString()) {
    std::string name = doc["name"].GetString();
    std::cout << "Name: " << name << std::endl;
  }
  if (doc.HasMember("age") && doc["age"].IsInt()) {
    int age = doc["age"].GetInt();
    std::cout << "Age: " << age << std::endl;
  }

  // 关闭 socket
  close(sockfd);

  return 0;
}

#include <iostream>
#include <string>
#include <sstream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

int main() {
  const char* port = "12345";  // 监听的端口号

  // 创建 socket
  struct addrinfo hints, *res;
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;
  getaddrinfo(nullptr, port, &hints, &res);
  int sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

  // 绑定端口号
  bind(sockfd, res->ai_addr, res->ai_addrlen);

  // 监听端口号
  listen(sockfd, 1);

  // 接受连接
  int client_sockfd = accept(sockfd, nullptr, nullptr);

  // 构造 JSON 数据
  rapidjson::Document doc;
  doc.SetObject();
  rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();
  doc.AddMember("name", "John", allocator);
  doc.AddMember("age", 25, allocator);

  // 序列化 JSON
  rapidjson::StringBuffer buffer;
  rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
  doc.Accept(writer);

  // 发送数据
  std::string data = buffer.GetString();
  send(client_sockfd, data.c_str(), data.length(), 0);

  // 关闭 socket
  close(client_sockfd);
  close(sockfd);

  return 0;
}

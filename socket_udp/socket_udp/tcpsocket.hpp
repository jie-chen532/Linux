#include<unistd.h>
#include<iostream>
#include<stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<stirng>
#include<cstdio>
using namespace std;

#define BACKLOG 5

class TcpSocket
{
  private:
    int _sockfd;
  public:
    TcpSocket()
      ;_sockfd(-1)
      {}
    //创建套接字
    bool Socket()
    {
      _sockfd = socket(AF_INET,SOCK_STREAM, IPPROTO_TCP);
      if(_sockfd < 0)
      {
        perror("socket error");
        return false;
      }
      return true;
    }

    //绑定地址信息
    bool Bind(const string& ip, const uint16_t port)
    {
      struct sockaddr_in addr;
      addr.sin_family = AF_INET;
      addr.sin_port = htons(port);
      addr.sin_addr.s_addr = inet_addr(ip.c_str());
      int len = sizeof(struct sockaddr_in);
      int ret = bind(_sockfd, (struct sockaddr*)&addr, len);
      if(ret < 0)
      {
        perror("Bind error");
        return false;
      }
      return true;
    }
    
    //监听
    bool Listen(int backlog = BACKLOG)
    {
      int ret = listen(_sockfd, backlog);
      if(ret < 0)
      {
        perror("listen error");
        return false;
      }
      return true;
    }

    //发送连接请求
    bool Connect(string& ip, int& port)
    {
      struct sockaddr_in server_add;
      server_add.sin_family = AF_INET;
      server_add.sin_port = htons(port);
      server_add.sin_addr.s_addr = inet_addr(ip.c_str());

    }
}

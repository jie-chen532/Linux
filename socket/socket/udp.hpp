#include<iostream>
using namespace std;
#include<sys/socket.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>
#include<cstdio>
#include<netinet/in.h>
#define CHECK(p) if(p == false) {return -1;}

class UDPSocket
{
  public:

    UDPSocket() 
      :_sockfd(-1)
    {}

    //创建套接字
    bool Socket()
    {
      _sockfd = socket(AF_INET, SOCK_DGRAM,IPPROTO_UDP);
      if(_sockfd < 0)
      {
        perror("create socket error");
        return false;
      }
      return true;
    }


    //绑定信息
    bool Bind(const string& ip, const uint16_t& port)
    {
      struct sockaddr_in addr;
      addr.sin_family = AF_INET;
      //主机字节序转换为网络字节序
      addr.sin_port = htons(port);
      //将字符串的点分十进制ip地址转换为网络字节序的整数形式ip地址
      addr.sin_addr.s_addr = inet_addr(ip.c_str());
      int len = sizeof(addr);
      int ret = bind(_sockfd, (sockaddr*)&addr,len);
      if(ret < 0)
      {
        perror("bind error");
        return false;
      }
      return true;
    }


    //发送数据
    bool Send(string& data, const string& ip, const uint16_t& port)
    {
      sockaddr_in peeraddr;
      peeraddr.sin_family = AF_INET;
      peeraddr.sin_port = htons(port);
      peeraddr.sin_addr.s_addr = inet_addr(ip.c_str());
      socklen_t len = sizeof(sockaddr_in);
      int ret = sendto(_sockfd, data.c_str(), data.size(), 0, (sockaddr*)&peeraddr, len);
      if(ret < 0)
      {
        perror("send error");
        return false;
      }
      return true;
    }


    //接收数据
    bool Recv(string& data, string* ip = NULL, int* port = NULL)
    {
      char tmp[4096] = {0};
      sockaddr_in srcaddr;
      socklen_t len = sizeof(srcaddr);
      int ret = recvfrom(_sockfd, tmp, 4095, 0, (sockaddr*)&srcaddr,&len);
      if(ret < 0)
      {
        perror("recv error");
        return false;
      }
      
      data.assign(tmp, ret);

      if(port != NULL)
        *port = ntohs(srcaddr.sin_port);
      if(ip != NULL)
        *ip = inet_ntoa(srcaddr.sin_addr);
      return true;
    }

    //关闭套接字
    bool Close()
    {
      if(_sockfd != -1)
      {
        close(_sockfd);
        _sockfd = -1;
      }
      return true;
    }

  private:
    int _sockfd;
};

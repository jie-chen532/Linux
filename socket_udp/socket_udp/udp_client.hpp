#include<iostream>
#include<unistd.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<stdio.h>
using namespace std;


class Udp_client
{
  private:
    int _sockfd;
  public:
    Udp_client()
      :_sockfd(-1) {}
    //创建套接字
    bool sock()
    {
      _sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
      if(_sockfd < 0)
      {
        perror("sock error");
        return false;
      }
      return true;
    }

    //绑定ip+port
    bool Bind(string& ip, uint16_t port)
    {
      struct sockaddr_in addr;
      addr.sin_family = AF_INET;
      addr.sin_port = htons(port);
      addr.sin_addr.s_addr = inet_addr(ip.c_str());
      int len = sizeof(struct sockaddr_in);
      int ret = bind(_sockfd, (struct sockaddr*)&addr, len);
      if(ret < 0)
      {
        perror("bind error");
        return false;
      }
      return true;
    }

    //发送数据
    bool Send(string& buf, const string& ip, const int& port)
    {
      struct sockaddr_in srcaddr;//对端地址
      srcaddr.sin_family = AF_INET;
      srcaddr.sin_port = htons(port);
      srcaddr.sin_addr.s_addr = inet_addr(ip.c_str());
      int len = sizeof(sockaddr_in);
      int ret = sendto(_sockfd, buf.c_str(), buf.size(), 0, (sockaddr*)&srcaddr, len);
      if(ret < 0)
      {
        perror("send error");
        return false;
      }
      return true;
    }

    //接收数据
    bool Rev(string* buf, string* ip = NULL, int* port = NULL)
    {
      struct sockaddr_in srcaddr;//源端地址
      char tmp[4096] = {0};
      socklen_t len = sizeof(struct sockaddr_in);
      int ret = recvfrom(_sockfd, tmp, 4095, 0, (struct sockaddr*)&srcaddr, &len);//返回实际发送的数据长度
      if(ret < 0)
      {
        perror("Rev error");
        return false;
      }
      buf->assign(tmp, ret);//自带开辟空间的拷贝
      if(ip != NULL)
      {
        *ip = inet_ntoa(srcaddr.sin_addr);
      }
      if(port != NULL)
      {
        *port = ntohs(srcaddr.sin_port);
      }
      return true;
    }

    //关闭套接字
    bool Close()
    {
      if(_sockfd != -1)
      {
        close(_sockfd);
      }
      return true;
    }
};


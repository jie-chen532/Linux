#include<iostream>
using namespace std;
#include<arpa/inet.h>
#include<unistd.h>
#include<cstdio>

#define BACKLOG_MAX 5
#define CHECK(p) if(p==false) {return -1;}

class TcpSocket
{
  public:

    TcpSocket()
      :_sockfd(-1)
    {}

    //创建套接字
    bool Socket()
    {
      _sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
      if(_sockfd < 0)
      {
        perror("create socket error");
        return false;
      }
      return true;
    }


    //绑定地址信息
    bool Bind(const string& ip, const uint16_t& port)
    {
      sockaddr_in addr;
      addr.sin_family = AF_INET;
      addr.sin_port = htons(port);
      addr.sin_addr.s_addr = inet_addr(ip.c_str());
      socklen_t len = sizeof(addr);
      int ret = bind(_sockfd, (sockaddr*)&addr, len);
      if(ret < 0)
      {
        perror("bind error");
        return false;
      }
      return true;
    }

    //开始监听
    bool Listen(int backlog = BACKLOG_MAX)
    {
      int ret = listen(_sockfd, backlog);
      if(ret < 0)
      {
        perror("Listen error");
        return false;
      }
      return true;
    }

    //客户端发送连接请求
    bool Connect(const string& ip, const uint16_t& port)
    {
      sockaddr_in seraddr;//服务端地址信息
      seraddr.sin_family = AF_INET;
      seraddr.sin_port = htons(port);
      seraddr.sin_addr.s_addr = inet_addr(ip.c_str());
      socklen_t len = sizeof(sockaddr_in);
      int ret = connect(_sockfd, (sockaddr*)&seraddr, len);
      if(ret < 0)
      {
        perror("connect failed");
        return false;
      }
      return true;
    }

    //服务端获取新建连接
    bool Accept(TcpSocket& tcpsocket, string* ip = NULL, uint16_t* port = NULL)
    {
      sockaddr_in cliaddr;
      socklen_t len = sizeof(sockaddr_in);
      int ret = accept(_sockfd, (sockaddr*)&cliaddr, &len);
      if(ret < 0)
      {
        perror("accept error");
        return false;
      }
      tcpsocket._sockfd = ret;
      if(ip != NULL)
        *ip = inet_ntoa(cliaddr.sin_addr);
      if(port != NULL)
        *port = ntohs(cliaddr.sin_port);
      return true;
    }

    //发送数据
    //要发送整条数据
    bool Send(string& buf)
    {
      int total = 0;
      while(total < buf.size())
      {

        int ret = send(_sockfd, buf.c_str() + total, buf.size() - total, 0);
        if(ret < 0)
        {
          perror("send data failed");
          return false;
        }
        total += ret;
      }
      return true;
    }

    //接收数据
    bool Recv(string& buf)
    {
      char tmp[4096] = {0};
      int ret = recv(_sockfd, tmp, 4095, 0);
      if(ret < 0)
      {
        perror("recv error");
        return false;
      }
      else if(ret == 0)
      {
        cout << "connect is broken" << endl;
        return false;
      }
      buf.assign(tmp, ret);
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

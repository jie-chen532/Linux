#include"tcp.hpp"
#include<pthread.h>

void* pthread_comm(void* newSocket)
{
  TcpSocket* Socket = (TcpSocket*)newSocket;
  while(1)
  {
    bool ret;
    //接收数据
    string buf;
    ret = Socket->Recv(buf);
    if(ret == false)
    {
      Socket->Close();
      delete Socket;
      return NULL;
    }
    cout << "client say:" << buf << endl;

    buf.clear();
    //发送数据
    cout << "server say:";
    getline(cin, buf);
    ret = Socket->Send(buf);
    if(ret == false)
    {
      Socket->Close();
      delete Socket;
      return NULL;
    }
  }
  Socket->Close();
  delete Socket;
  return NULL;
}

int main()
{
  TcpSocket lst_socket;
  //创建套接字
  CHECK(lst_socket.Socket());
  //绑定地址信息
  CHECK(lst_socket.Bind("192.168.134.141", 9000));
  //开始监听
  CHECK(lst_socket.Listen());
  while(1)
  {
    //获取新建连接
    TcpSocket* newSocket = new TcpSocket;
    string ip;
    uint16_t port;
    bool ret = lst_socket.Accept(*newSocket, &ip, &port);
    if(ret == false)
      continue;
    cout << "new connect-->ip:" << ip << " port:" << port << endl;

    //获取新建连接之后，创建线程负责与客户端进行通信
    pthread_t tid;
    int res = pthread_create(&tid, NULL, pthread_comm, (void*)newSocket);
    if(res != 0)
    {
      perror("create pthread failed");
      continue;
    }
    //线程分离
    pthread_detach(tid);
  }
  //关闭套接字
  lst_socket.Close();
  return 0;
}

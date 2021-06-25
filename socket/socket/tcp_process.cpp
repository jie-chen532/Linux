#include"tcp.hpp"
#include<stdlib.h>
#include<signal.h>

void work(TcpSocket& newSocket)
{
  //接收数据
  while(1)
  {
    bool ret;
    string buf;
    ret = newSocket.Recv(buf);
    if(ret == false)
    {
      newSocket.Close();
      exit(0);
    }
    cout << "client say:" << buf << endl;

    buf.clear();
    //发送数据
    cout << "server say:";
    getline(cin, buf);
    ret = newSocket.Send(buf);
    if(ret == false)
    {
      newSocket.Close();
      exit(0);
    }
  }
  newSocket.Close();
  return;
}

int main()
{
  signal(SIGCHLD, SIG_IGN);//信号函数，如果有子进程退出，忽略它的退出原因
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
    TcpSocket newSocket;
    string ip;
    uint16_t port;
    bool ret = lst_socket.Accept(newSocket, &ip, &port);
    if(ret == false)
      continue;
    cout << "new connect  ip:" << ip << "  port:" << port << endl;

    //创建子进程，子进程与客户端进行通信
    pid_t pid = fork();
    if(pid < 0)
    {
      perror("create fork failed");
      newSocket.Close();
      continue;
    }
    else if(pid == 0) //子进程
    {
      work(newSocket);
    }
    //父进程
    //子进程用来通信，父进程的通信套接字就可以关闭了，防止资源泄漏
    //父子进程数据独有，父进程关闭不会对子进程造成影响
    newSocket.Close();
  }
  //关闭套接字
  lst_socket.Close();
  return 0;
}

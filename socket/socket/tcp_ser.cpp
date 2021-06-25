#include"tcp.hpp"

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
    TcpSocket newSocket;
    string ip;
    uint16_t port;
    bool ret = lst_socket.Accept(newSocket, &ip, &port);
    if(ret == false)
      continue;
    cout << "new connect  ip:" << ip << "  port:" << port << endl;

    //接收数据
    string buf;
    ret = newSocket.Recv(buf);
    if(ret == false)
    {
      newSocket.Close();
      continue;
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
    }
  }
  //关闭套接字
  lst_socket.Close();
  return 0;
}

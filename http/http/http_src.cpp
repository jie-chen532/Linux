#include"tcp.hpp"
#include<sstream>

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

    //接收数据
    string buf;
    ret = newSocket.Recv(buf);
    if(ret == false)
    {
      newSocket.Close();
      continue;
    }
    cout << "request:[" << buf  << "]\n"<< endl;

    buf.clear();
    //发送数据
    //组织数据格式
    stringstream ss;
    string body = "<html><body><h1>Hello World</h1></body></html>";
    ss << "HTTP/1.1 200 OK\r\n";
    ss << "Content-Length: " << body.size() << "\r\n";
    ss << "Content-Type: text/html;charset=UTF-8\r\n";
    ss << "Connection: close\r\n";
    ss << "Location: https://www.baidu.com\r\n";
    ss << "\r\n";
    ss << body;
    buf = ss.str();
    cout << "response:[" << buf << "]\n" << endl;
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

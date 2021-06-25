#include"tcp.hpp"

int main()
{
  TcpSocket cli_socket;

  //创建套接字
  CHECK(cli_socket.Socket());

  //绑定地址信息(不推荐)

  //向服务器发送连接请求
  CHECK(cli_socket.Connect("192.168.134.141", 9000));

  while(1)
  {
    //发送数据
    string buf;
    cout << "client say:" ;
    getline(cin, buf);
    
    CHECK(cli_socket.Send(buf));
  
    buf.clear();
    //接收数据
    CHECK(cli_socket.Recv(buf));
    cout << "serve say:" << buf << endl;
  }
  //关闭套接字
  cli_socket.Close();
  return 0;
}

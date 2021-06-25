#include"udp.hpp"

int main()
{
  UDPSocket sock_cli;
  //创建套接字
  CHECK(sock_cli.Socket());

  //绑定地址信息(不推荐)
  
  while(1)
  {
    //发送数据
    string buf;
    cout << "client say:";
    getline(cin, buf);
    CHECK(sock_cli.Send(buf, "192.168.134.141", 9000));

    buf.clear();
    
    //接收数据
    CHECK(sock_cli.Recv(buf));

    cout << "server say:" << buf << endl;
    
  }

  //关闭套接字
  sock_cli.Close();
  return 0;
}

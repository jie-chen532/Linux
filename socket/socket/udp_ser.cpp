#include"udp.hpp"

int main()
{
  UDPSocket sock;
  //创建套接字
  CHECK(sock.Socket());

  //绑定地址信息
  CHECK(sock.Bind("192.168.134.141",9000 ));

  while(1)
  {
    //接收数据
    string data;
    string ip;
    int port;
    bool ret = sock.Recv(data, &ip, &port);
    if(ret == false)
      continue;
    cout << "cli_ip:" << ip <<" port:" << port << " say:"<< data<< endl; 
    
    //发送数据
    data.clear();
    cout << "serve say:";
    getline(cin, data);
    ret = sock.Send(data, ip, port);
    if(ret == false)
    {
      cout << "serve say failed" << endl;
    }
  }

  //关闭套接字
  sock.Close();
  return 0;
}

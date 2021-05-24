#include"udp_client.hpp"
#define CHECKRET(p) if((p) == false){return -1;}
int main()
{
  //创建套接字
  Udp_client client;
  CHECKRET(client.sock());
  //绑定ip+port(不推荐绑定)
  while(1){
    //发送数据
    string buf;
    cout << "client say:";
    cin >> buf;
    string ip = "192.168.134.141";
    CHECKRET(client.Send(buf, ip, 9000));
    //接收数据
    buf.clear();
    CHECKRET(client.Rev(&buf));
    cout << "server say:" << buf << endl;
  }
  //关闭套接字
  client.Close();
  return 0;
}

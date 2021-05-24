#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<string.h>
int main()
{
  //创建套接字
  //socket(int domain, int type, int protocol)
  int socketfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  if(socketfd < 0)
  {
    perror("socket error");
    return -1;
  }
  //绑定地址信息
  //int bind(int socketfd, struct sockaddr* sockaddr, socklen_t addlen)
  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_port = htons(9000);
  addr.sin_addr.s_addr = inet_addr("192.168.134.141");
  int len = sizeof(struct sockaddr_in);
  int ret = bind(socketfd, (struct sockaddr*)&addr, len);
  if(ret < 0)
  {
    perror("bind error");
    return -1;
  }
  //因为是服务器，所以会一直接收数据，发送数据
  while(1)
  {
    //接收数据
    //recvfrom(int socketfd, void* buf, int len, int flag, struct sockaddr* addr, socklen_t* addrlen);
    char buf[1024] = {0};
    struct sockaddr_in srcaddr;//源端地址
    ret = recvfrom(socketfd, buf, 1023, 0, (struct sockaddr*)&srcaddr, &len);
    if(ret < 0)
    {
      perror("recvfrom error");
      return -1;
    }
    uint16_t client_port = ntohs(srcaddr.sin_port);
    char* client_ip = inet_ntoa(srcaddr.sin_addr);
    printf("%s--%d\n", client_ip, client_port);
    printf("client say:%s\n", buf);
    //发送数据
    //ssize_t sendto(int sockfd, void* data, int len, int flag, struct sockaddr* peeraddr, socklen_t addrlen)
    memset(buf, 0x00, 1024);
    printf("server say:");
    fflush(stdout);
    fgets(buf, 1023, stdin);
    ret = sendto(socketfd, buf, strlen(buf), 0, (struct sockaddr*)&srcaddr, sizeof(struct sockaddr_in));
    if(ret < 0)
    {
      perror("sendto error");
      return -1;
    }
  }
  //关闭套接字
  //int close(int sockfd);
  close(socketfd);
  return 0;
}

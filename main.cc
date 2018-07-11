#include <iostream>
#include <string>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include "ota_file_class.h"

using namespace std;

#define MYPORT   5566    //服务器端口
#define BACKLOG  20   //多少等待链接控制
int main(int argc,char *argv[])
{
  //更新文件处理部分
  cout<<"socket project 02"<<endl;
  //Firmware firm("./firmware/firmware_2.0.bin");
  //long len = firm.GetFileLength();
  //string firm_buf;
  //firm_buf = firm.GetFileString();
  //cout<<firm_buf<<endl;
  //sock处理部分
  int sockfd,newfd;// listen on sockfd socket and accept on newfd
  struct sockaddr_in service_addr;  
  struct sockaddr_in client_addr;
  int sin_size;
  cout<<"create a socket"<<endl;
  if((sockfd=socket(AF_INET,SOCK_STREAM,0))==-1)  //创建一个socket描述符
  {
    perror("socket"); // 在系统打印的错误信息之前加入perror的内容，方便定位
    exit(1);
  }
  //设置IP TCP 和端口
  service_addr.sin_family = AF_INET;
  service_addr.sin_port = htons(MYPORT);
  service_addr.sin_addr.s_addr = inet_addr("0.0.0.0");  //自动适应服务器IP
  memset(&(service_addr.sin_zero),0,8);
  //帮顶socket和IP端口
  if(bind(sockfd,(struct sockaddr*)&service_addr,sizeof(struct sockaddr))==-1)
  {
    perror("bind");
    exit(1);
  }

    cout<<"start listening"<<endl;
  //监听端口
  if(listen(sockfd,BACKLOG)==-1)
  {
    perror("listen");
    exit(1);
  }
  //连接端口并处理
  sin_size = sizeof(struct sockaddr_in);
  cout<<"loop start"<<endl;
  int i=0;
  while(1)
  {
    cout<<"count　:"<<i++<<endl;
    sin_size = sizeof(struct sockaddr_in);
    if((newfd = accept(sockfd,(struct sockaddr*)&client_addr,(socklen_t*)&sin_size))==-1)
    {
      cout<<"accept"<<endl;
      perror("accept");
      continue;
    }
    cout<<"Client IP"<<inet_ntoa(client_addr.sin_addr)<<endl;
    if(!fork())  //child process
    {
      
      if(send(newfd,"haha",4,0)==-1)
      {
        perror("send");
      }
      close(newfd);
      while(waitpid(-1,NULL,WNOHANG)>0);
    }
    
  }
  return 0;
}





























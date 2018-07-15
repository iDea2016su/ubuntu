#include <iostream>
#include <string>
#include <json/json.h>
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
#include "ota_string_class.h"
#include "terminal_reply_class.h"

using namespace std;
using namespace Json;

#define MYPORT   5566    //服务器端口
#define BACKLOG  20   //多少等待链接控制
int main(int argc,char *argv[])
{
  //更新文件处理部分
  cout<<"socket project 02"<<endl;
  Firmware firm("./firmware/firmware_2.0.bin");
  long len = firm.GetFileLength();
  string firm_buf;
  firm_buf = firm.GetFileString();
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
  service_addr.sin_addr.s_addr = htonl(INADDR_ANY);  //自动适应服务器IP
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
  //Json 对象
  Reader  reader;
  Value   value;
  //连接端口并处理
  sin_size = sizeof(struct sockaddr_in);
  cout<<"loop start"<<endl;
  int i=0;
  while(1)
  {

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
	  char * terminal_request = (char*)malloc(500*sizeof(char));
	  TerminalReply huka_terminal_replay(newfd);
	  while(1)
	  {
		if(recv(newfd,terminal_request,500,0)==-1)
		{ 
			cout<<"can not get first terminal pack"<<endl;
			close(newfd);
			exit(0);
		}
			string json_buf = terminal_request;
		if(reader.parse(json_buf,value))
		{
		  if(!value["imei"].isNull())  //第一个升级包上报IMEI的处理
			{
					// To do database
					cout<<"device imei:"<<value["imei"].asString()<<endl;
					cout<<"device soft version:"<<value["software_version"].asString()<<endl;
					cout<<"device hard version:"<<value["hardware_version"].asString()<<endl;
					if(huka_terminal_replay.Send("imeirep","00543","0103","end")==-1)
					{
						free(terminal_request);
		  				cout<<"can not reply imei"<<endl;
		  				close(newfd);
		  			    exit(0);
					}
					//To replay terminal
			}
		  if(!value["pack_num"].isNull())  //固件内容申请包
		    {
			  // To do database
			  cout<<"pack_number:"<<value["pack_num"].asInt()<<endl;
			  //To replay terminal
		    }
		  if(!value["pack_status"].isNull())  //固件升级完成上报
		    {
			  // To do database
			  cout<<"pack_number:"<<value["pack_status"].asInt()<<endl;
			  //To replay terminal
		    }
		}
		else
		{
		  free(terminal_request);
		  cout<<"can not get imei"<<endl;
		  close(newfd);
		  exit(0);
		}
	 }
	 free(terminal_request);          
	 cout<<"update finish"<<endl;
	 close(newfd);
	 exit(0);
	}
	while(waitpid(-1,NULL,WNOHANG)>0);
  }
  return 0;
}




































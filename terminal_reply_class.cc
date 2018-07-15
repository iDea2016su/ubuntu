#include "terminal_reply_class.h"
#include <sys/types.h>
#include <sys/socket.h>
using namespace std;
TerminalReply::TerminalReply(int psocket)
{
	socket_ = psocket;
}
int TerminalReply::Send(string ps1)
{
   	if(send(socket_,ps1.c_str(),ps1.length(),0)==-1)
   	{
   		return -1;
   	}
   	return 0;

}
int TerminalReply::Send(string ps1,string ps2)
{
	ps1 += ps2;
   	if(send(socket_,ps1.c_str(),ps1.length(),0)==-1)
   	{
   		return -1;
   	}
   	return 0;

}
int TerminalReply::Send(string ps1,string ps2, string ps3)
{
	ps1 = ps1 + ps2 + ps3;
   	if(send(socket_,ps1.c_str(),ps1.length(),0)==-1)
   	{
   		return -1;
   	}
   	return 0;

}
int TerminalReply::Send(string ps1,string ps2,string ps3,string ps4)
{
	ps1 = ps1 + ps2 + ps3 + ps4;
   	if(send(socket_,ps1.c_str(),ps1.length(),0)==-1)
   	{
   		return -1;
   	}
   	return 0;

}
int TerminalReply::Send(string ps1,string ps2,string ps3,string ps4,string ps5)
{
	ps1 = ps1 + ps2 + ps3 + ps4 + ps5;
   	if(send(socket_,ps1.c_str(),ps1.length(),0)==-1)
   	{
   		return -1;
   	}
   	return 0;

}
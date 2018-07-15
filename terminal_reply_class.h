#ifndef TERMINAL_REPLY_CLASS
#define TERMINAL_REPLY_CLASS
#include <string>
class TerminalReply
{
public:
	TerminalReply(int psocket);
	int Send(std::string ps1);
	int Send(std::string ps1,std::string ps2);
	int Send(std::string ps1,std::string ps2,std::string ps3);
	int Send(std::string ps1,std::string ps2,std::string ps3,std::string ps4);
	int Send(std::string ps1,std::string ps2,std::string ps3,std::string ps4,std::string ps5);
private:
	int socket_;
};
#endif
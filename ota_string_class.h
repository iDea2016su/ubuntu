#ifndef OTA_STRING_CLASS
#define OTA_STRING_CLASS
#include <string>

class OtaString
{
public:
	OtaString(std::string pstring);
	~OtaString();
	std::string GetPack(int start,int end);
private:
	std::string ota_buf_;
	int length_;
	int start_;
	int end_;
};
#endif
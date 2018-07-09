#ifndef OTA_FILE_CLASS_H
#define OTA_FILE_CLASS_H
#include <string>
class Firmware
{
  public:
  Firmware(const char* name);
  long GetFileLength();
  int GetFileBuf(unsigned char *buf);
  std::string GetFileString();

  private :
  char *file_name_;
  long file_length_;
  std::string file_string_;
};

#endif

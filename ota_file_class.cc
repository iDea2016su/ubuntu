#include "ota_file_class.h"
#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

Firmware::Firmware(const char *name)
{
  file_name_ = (char *)name;
  fstream firmBinFile;
  firmBinFile.open(file_name_);  //C++中，open　是　void 函数，在　ｃ中是整型
  if(!(firmBinFile))
  {
    cout<<"Get length but can not open file"<<endl;
  }
  firmBinFile.seekg(0,ios::end);
  file_length_ = firmBinFile.tellg();
  firmBinFile.seekg(0,ios::beg);
  unsigned char * buf = (unsigned char*)malloc(file_length_*sizeof(char));
  GetFileBuf(buf);
	for(long i=0;i<file_length_;i++)
	  {
	    char tmp = buf[i]/16+'0';
	    if(tmp>'9')
	    {
	      tmp+=7;
	    }
	    file_string_ += tmp;
	    tmp = buf[i]%16+'0';
	    if(tmp>'9')
	    {
	      tmp+=7;
	    }
	    file_string_ += tmp;
	  }
  firmBinFile.close();
  free(buf);
};

long  Firmware::GetFileLength()
{
  return file_length_;  
};
int Firmware::GetFileBuf(unsigned char* buf)
{
  fstream firmBinFile;
  firmBinFile.open(file_name_);  //C++中，open　是　void 函数，在　ｃ中是整型
  if(!(firmBinFile))
  {
    cout<<"can not open file"<<endl;
    return 0;
  }
  for(long i=0;i<file_length_;i++)
  {
    char tmp;
    firmBinFile.read(&tmp,1);
    buf[i] = tmp; 
  }
  firmBinFile.close();
  return 1;  
};

string Firmware::GetFileString(void)
{
  return file_string_;
}

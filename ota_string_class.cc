#include "ota_string_class.h"
#include <stdlib.h>
#include <iostream>
#include <string.h>
using namespace std;
OtaString::OtaString(string pstring)
{
	ota_buf_ = pstring;
	length_ = ota_buf_.length();
	start_ = 0;
	end_ = 0;
}
string OtaString::GetPack(int start,int plength)
{
	if(start<0||start>length_)
	{
		cout<<"Get pack error"<<endl;
		return NULL;
	}
	char * tmp = (char*)malloc(plength*sizeof(char)+1);
	memset(tmp,0,plength+1);
	for(int i=0;i<plength;i++)
	{
        tmp[i] = ota_buf_[start+i];
	}
	string result = tmp;
	free(tmp);
	return result;
}
string OtaString::GetFormotStringFromInt(int plength,int value)
{
	char * tmp = (char*)malloc(plength*sizeof(char)+1);
	memset(tmp,plength+1,0);
	memset(tmp,plength,'0');
	string v = to_string(value);
    int l = v.length();
	for(int i=0;i<l;i++)
	{
		tmp[plength-i] = v[l-i];
	}
    string result;
    for(int i=0;i<plength;i++)
    {
    	result[i] = tmp[i];
    } 
    free(tmp);
    return result;
}
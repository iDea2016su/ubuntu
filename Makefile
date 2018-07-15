
objects = main.o ota_file_class.o ota_string_class.o terminal_reply_class.o

cc = g++ 

main : clean $(objects)
	$(cc) -o main $(objects) -ljson 

main.o : ota_file_class.h

ota_file_class.o : ota_file_class.h

ota_string_class.o : ota_string_class.h
	g++   -std=c++11 -c -o ota_string_class.o ota_string_class.cc 
terminal_reply_class.o : terminal_reply_class.h

.PHONY : clean

clean : 
	-rm main $(objects)


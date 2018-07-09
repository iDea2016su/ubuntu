
objects = main.o ota_file_class.o

cc = g++ 


main : clean $(objects)
	$(cc) -o main $(objects)

main.o : ota_file_class.h

ota_file_class.o : ota_file_class.h

.PHONY : clean

clean : 
	rm main $(objects)


CC = g++

FLAGS = -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations \
		-Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions -Wcast-qual        \
		-Wconversion -Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op                 \
		-Wmissing-field-initializers -Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstack-usage=8192         \
		-Wstrict-aliasing -Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -D_DEBUG -D_EJUDGE_CLIENT_SIDE


all: do

clean:
	rm *.o do.exe
	
main: main.cpp
	$(CC) $(FLAGS) -c main.cpp -o main.o

file: file.cpp
	$(CC) $(FLAGS) -c file.cpp -o file.o

sort: sort.cpp
	$(CC) $(FLAGS) -c sort.cpp -o sort.o

do: main file sort
	$(CC) $(FLAGS) main.o file.o sort.o -o do.exe
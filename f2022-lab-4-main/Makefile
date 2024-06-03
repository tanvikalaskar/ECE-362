CFLAGS=-O0 -g

all: lab4.o autograder.x86_64.o
	g++ $(CFLAGS) autograder.x86_64.o lab4.o -o lab4

lab4.o: lab4.cc
	g++ $(CFLAGS) -c lab4.cc -o lab4.o

MacArm: lab4.o autograder.mac.arm64e.o
	g++ $(CFLAGS) autograder.mac.arm64e.o lab4.o -o lab4

clean:
	rm -f lab4.o lab4

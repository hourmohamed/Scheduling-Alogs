all: lab6

lab6: lab6.o Process.o Scheduler.o FCFS.o RoundRobin.o SPN.o  SRT.o HRRN.o  FB2i.o Aging.o FB_1.o
	g++ lab6.o Process.o Scheduler.o FCFS.o RoundRobin.o SPN.o  SRT.o HRRN.o FB2i.o Aging.o FB_1.o -o  lab6

lab6.o: main.cpp
	g++ -c main.cpp -o lab6.o

Process.o: Process.cpp
	g++ -c Process.cpp -o Process.o

Scheduler.o: Scheduler.cpp
	g++ -c Scheduler.cpp -o Scheduler.o

FCFS.o: FCFS.cpp
	g++ -c FCFS.cpp -o FCFS.o
RoundRobin.o: RoundRobin.cpp
	g++ -c RoundRobin.cpp -o RoundRobin.o

SPN.o: SPN.cpp
	g++ -c SPN.cpp -o SPN.o
SRT.o: SRT.cpp
	g++ -c SRT.cpp -o SRT.o

HRRN.o: HRRN.cpp
	g++ -c HRRN.cpp -o HRRN.o	

FB_1.o: FB_1.cpp
	g++ -c FB_1.cpp -o FB_1.o	

FB2i.o: FB2i.cpp
	g++ -c FB2i.cpp -o FB2i.o

Aging.o: Aging.cpp
	g++ -c Aging.cpp -o Aging.o

clean:
	rm -f *.o lab6

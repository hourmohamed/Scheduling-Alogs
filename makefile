all: main

main: main.o Process.o Scheduler.o FCFS.o RoundRobin.o SPN.o  SRT.o HRRN.o
	g++ main.o Process.o Scheduler.o FCFS.o RoundRobin.o SPN.o  SRT.o HRRN.o -o main 

main.o: main.cpp
	g++ -c main.cpp -o main.o

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
clean:
	rm -f *.o main

all: main

main: main.o Process.o Scheduler.o FCFS.o
	g++ main.o Process.o Scheduler.o FCFS.o -o main

main.o: main.cpp
	g++ -c main.cpp -o main.o

Process.o: Process.cpp
	g++ -c Process.cpp -o Process.o

Scheduler.o: Scheduler.cpp
	g++ -c Scheduler.cpp -o Scheduler.o

FCFS.o: FCFS.cpp
	g++ -c FCFS.cpp -o FCFS.o

clean:
	rm -f *.o main

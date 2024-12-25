#ifndef PROCESS_H
#define PROCESS_H

class Process {
public:
    char name;
    int arrivalTime;
    int serviceTime;
    int finishTime=0;
    int turnAroundTime=0;
    int normTurn=0;
    int remainingTime;
    Process(char name, int arrivalTime, int serviceTime);
//remainingTime(service), finishTime(0), turnAroundTime(0), normTurn(0.0) {}

    
};

#endif // PROCESS_H

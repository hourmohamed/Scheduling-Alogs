#ifndef PROCESS_H
#define PROCESS_H

class Process {
public:
    char name;
    int arrivalTime;
    int serviceTime;
    int finishTime;
    int turnAroundTime;
    int normTurn;

    Process(char name, int arrivalTime, int serviceTime);


    
};

#endif // PROCESS_H

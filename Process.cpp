#include "Process.h"

Process::Process(char name, int arrivalTime, int serviceTime,int time_line) {
    this->name = name;
    this->arrivalTime = arrivalTime;
    this->serviceTime = serviceTime;
    this->remainingTime = serviceTime;  // Initialize remaining time to service time
    this->finishTime = 0;
    this->turnAroundTime = 0;
    this->normTurn = 0;
    for (int i=0;i<time_line;i++)
        state[i]=-1;
}

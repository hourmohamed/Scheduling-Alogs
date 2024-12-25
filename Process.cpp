#include "Process.h"

Process::Process(char name, int arrivalTime, int serviceTime) {
    this->name = name;
    this->arrivalTime = arrivalTime;
    this->serviceTime = serviceTime;
    this->remainingTime = serviceTime;  // Initialize remaining time to service time
    this->finishTime = 0;
    this->turnAroundTime = 0;
    this->normTurn = 0;
}

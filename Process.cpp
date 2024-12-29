#include "Process.h"
#include <iostream>
using namespace std;

Process::Process(char name, int arrivalTime, int serviceTime, int time_line) {
    this->name = name;
    this->arrivalTime = arrivalTime;
    this->serviceTime = serviceTime;
    this->remainingTime = serviceTime;
    this->finishTime = 0;
    this->turnAroundTime = 0;
    this->normTurn = 0;
    this->feedback_queue=0;
    this->done=false;
    state.resize(time_line, -1);
}



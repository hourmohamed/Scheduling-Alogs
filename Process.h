#ifndef PROCESS_H
#define PROCESS_H
#include <vector>
using namespace std;
class Process {
public:
    char name;
    int arrivalTime;
    int serviceTime;
    int finishTime=0;
    int turnAroundTime=0;
    int normTurn=0;
    int remainingTime;
    int time_line;
    int priority;
    vector<int> state;
    Process(char name, int arrivalTime, int serviceTime,int time_line);
//remainingTime(service), finishTime(0), turnAroundTime(0), normTurn(0.0) {}

    
};

#endif // PROCESS_H

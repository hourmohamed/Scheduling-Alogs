#include "FCFS.h"
#include <iostream>
#include <algorithm>
#include "Scheduler.h"

void FCFS::schedule(std::vector<Process>& processes) {

    std::cerr << "Scheduling using FCFS" << std::endl;

    int time = processes[0].arrivalTime;
    for (int i = 0; i < Scheduler::processes_count(processes); i++)
    {
        int processIndex = i;
        int arrivalTime = processes[i].arrivalTime;
        int serviceTime = processes[i].serviceTime;

        processes[i].finishTime = (time + serviceTime);
        processes[i].turnAroundTime = (processes[i].finishTime - arrivalTime);
        processes[i].normTurn = (processes[i].turnAroundTime * 1.0 / serviceTime);

        // for (int j = time; j < processes[i].finishTime; j++)
        //     timeline[j][processIndex] = '*';
        // for (int j = arrivalTime; j < time; j++)
        //     timeline[j][processIndex] = '.';
        // time += serviceTime;
    }
}

void sort_by_arrival(std::vector<Process>& processes) {
    std::sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.arrivalTime < b.arrivalTime;
    });
}

int FCFS::calculate_finish_time(Process p) {
    std::cerr <<"arrival time" << p.arrivalTime << std::endl;
    std::cerr << "service time" << p.serviceTime << std::endl;
    std::cerr << "finish time" << p.arrivalTime + p.serviceTime << std::endl;

    return p.arrivalTime + p.serviceTime;
}


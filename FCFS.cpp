#include "FCFS.h"
#include <iostream>
#include <algorithm>
#include "Scheduler.h"






void sort_by_arrival(std::vector<Process>& processes) {
    std::sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.arrivalTime < b.arrivalTime;
    });

}

int FCFS::calculate_finish_time(Process p){
    std::cerr <<"arrival time" << p.arrivalTime << std::endl;
    std::cerr << "service time" << p.serviceTime << std::endl;
    std::cerr << "finish time" << p.arrivalTime + p.serviceTime << std::endl;

    std::cerr << "finish time in fcfs" << p.arrivalTime + p.serviceTime << std::endl;

    return p.arrivalTime + p.serviceTime;
}


void FCFS::schedule(std::vector<Process>& processes) {

    std::cerr << "Scheduling using FCFS" << std::endl;

    // sort_by_arrival(processes);

    int time = processes[0].arrivalTime;
    
    std::vector<int> turnaround_times =calculate_turnaround(processes);
    std::vector<double> normTurn_times = calculate_normturn(processes);

    for (int i = 0; i < Scheduler::processes_count(processes); i++)
    {
        int processIndex = i;
        int arrivalTime = processes[i].arrivalTime;
        int serviceTime = processes[i].serviceTime;

        // processes[i].finishTime = (time + serviceTime);
         processes[i].finishTime = calculate_finish_time(processes[i]);

        // processes[i].turnAroundTime = (processes[i].finishTime - arrivalTime);
        processes[i].turnAroundTime = turnaround_times[i];
        // processes[i].normTurn = (processes[i].turnAroundTime * 1.0 / serviceTime);

        processes[i].normTurn = normTurn_times[i];

        // for (int j = time; j < processes[i].finishTime; j++)
        //     timeline[j][processIndex] = '*';
        // for (int j = arrivalTime; j < time; j++)
        //     timeline[j][processIndex] = '.';
        // time += serviceTime;
    }
}




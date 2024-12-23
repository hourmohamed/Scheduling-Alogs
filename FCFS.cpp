#include "common_functions.h"



void FCFS(std::vector<Process>& processes){

    int num_processes = processes_count(processes);

   int time = processes[0].arrival_time;
    for (int i = 0; i < num_processes; i++)
    {
        int processIndex = i;
        int arrivalTime = processes[i].arrival_time;
        int serviceTime = processes[i].service_time;
    }
}
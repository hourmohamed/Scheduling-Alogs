#include "RoundRobin.h"
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;
// Sort the processes by arrival time in ascending order
void RoundRobin::sort_by_arrival(std::vector<Process> &processes)
{
    std::sort(processes.begin(), processes.end(), [](const Process &a, const Process &b)
              { return a.arrivalTime < b.arrivalTime; });
}

// Calculate finish times for each process in RoundRobin
std::vector<int> RoundRobin::calculate_finish_times(std::vector<Process> &processes)
{
    std::vector<int> finish_times;
    int current_time = 0;

    std::queue<Process *> queue;
    for (auto &process : processes)
    {
        queue.push(&process);
    }

    while (!queue.empty())
    {
        Process *currentProcess = queue.front();
        queue.pop();

        int timeSlice = min(currentProcess->remainingTime, this->quantum);
        currentProcess->remainingTime -= timeSlice;
        current_time += timeSlice;

        if (currentProcess->remainingTime == 0)
        {
            finish_times.push_back(current_time);
        }
        else
        {
            queue.push(currentProcess);
        }
    }

    return finish_times;
}

void RoundRobin::schedule(std::vector<Process> &processes) {
    int current_time = 0;  // Current simulation time
    int index = 0;         // Tracks the next process to add to the ready queue
    std::queue<Process*> ready_queue;

    // Sort processes by arrival time
    sort_by_arrival(processes);

    while (index < processes.size() || !ready_queue.empty()) {
        // Add all processes that have arrived by the current time
        while (index < processes.size() && processes[index].arrivalTime <= current_time) {

            
            ready_queue.push(&processes[index]);
            index++;
        }

       
        if (ready_queue.empty()) {
            current_time = processes[index].arrivalTime;
            continue;
        }

      
        Process* current_process = ready_queue.front();
        ready_queue.pop();

       
        int time_slice = std::min(this->quantum, current_process->remainingTime);
        current_time += time_slice;
        current_process->remainingTime -= time_slice;

     
        if (current_process->remainingTime == 0) {
            current_process->finishTime = current_time;
            current_process->turnAroundTime = current_process->finishTime - current_process->arrivalTime;
            current_process->normTurn = static_cast<double>(current_process->turnAroundTime) / current_process->serviceTime;
        } else {
            
            ready_queue.push(current_process);
        }

       
       
    }

   
}


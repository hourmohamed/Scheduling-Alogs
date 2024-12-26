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
    // std::vector<int> finish_times;
    // int current_time = 0;
   
    // std::queue<Process *> queue;
    // for (auto &process : processes)
    // {
    //     queue.push(&process);
    // }

    // while (!queue.empty())
    // {
    //     Process *currentProcess = queue.front();
    //     queue.pop();

    //     int timeSlice = min(currentProcess->remainingTime, this->quantum);
    //     currentProcess->remainingTime -= timeSlice;
    //     current_time += timeSlice;

    //     if (currentProcess->remainingTime == 0)
    //     {   
    //         //cout <<current_time<<endl;
    //         finish_times.push_back(current_time);
    //     }
    //     else
    //     {
    //         queue.push(currentProcess);
    //     }
    // }

    // return finish_times;
    vector <int> finish_times;
    for (int i=0;i<processes.size();i++)
    {
        finish_times.push_back(processes[i].finishTime);
    }
    return finish_times;
}

void RoundRobin::schedule(std::vector<Process> &processes)
{
    int current_time = 0; 
    int number_of_processes = 0;       
    std::queue<Process *> ready_queue;

    sort_by_arrival(processes);

    while (number_of_processes < processes.size() || !ready_queue.empty())
    {
       
        while (number_of_processes < processes.size() && processes[number_of_processes].arrivalTime <= current_time)
        {
            processes[number_of_processes].state.at(current_time) = 0;
            ready_queue.push(&processes[number_of_processes]);
            number_of_processes++;
        }

        if (ready_queue.empty())
        {
            current_time = processes[number_of_processes].arrivalTime;
            continue;
        }

        Process *current_process = ready_queue.front();
        ready_queue.pop();

        int time_slice = std::min(this->quantum, current_process->remainingTime);
        current_time += time_slice;
        current_process->remainingTime -= time_slice;

        // Ensure we're updating the correct process state
        for (int i = current_time - time_slice; i < current_time; ++i)
            current_process->state.at(i) = 1; // Update state for current process

        if (current_process->remainingTime == 0)
        {
            current_process->finishTime = current_time;
            current_process->turnAroundTime = current_process->finishTime - current_process->arrivalTime;
            current_process->normTurn = static_cast<double>(current_process->turnAroundTime) / current_process->serviceTime;
        }
        else
        {
            // Recheck new processes that arrive at the current time
            while (number_of_processes < processes.size() && processes[number_of_processes].arrivalTime <= current_time)
            {
                processes[number_of_processes].state.at(current_time) = 0;
                ready_queue.push(&processes[number_of_processes]);
                number_of_processes++;
            }

            ready_queue.push(current_process); // Re-add current process to the queue
        }
    }
}

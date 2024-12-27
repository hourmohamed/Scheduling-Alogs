#include "SRT.h"
#include <iostream>
#include <algorithm>
#include <queue>
#include <climits>
using namespace std;
// Sort the processes by arrival time in ascending order
void SRT::sort_by_arrival(std::vector<Process> &processes)
{
    std::sort(processes.begin(), processes.end(), [](const Process &a, const Process &b)
              { return a.arrivalTime < b.arrivalTime; });
}

// Calculate finish times for each process in SRT
std::vector<int> SRT::calculate_finish_times(std::vector<Process> &processes)
{

    vector<int> finish_times;
    for (int i = 0; i < processes.size(); i++)
    {
        finish_times.push_back(processes[i].finishTime);
    }
    return finish_times;
}

void SRT::schedule(std::vector<Process> &processes)
{
    
    int current_time = 0;
    int number_of_processes = 0;
    int min_burst = 0;
    Process *min_process = nullptr;
    std::queue<Process *> ready_queue;
    std::queue<Process *> temp_queue;

    // Sort processes by arrival time
    sort_by_arrival(processes);

    while (number_of_processes < processes.size() || !ready_queue.empty())
    {
        // Add processes that have arrived to the ready queue
        while (number_of_processes < processes.size() && processes[number_of_processes].arrivalTime <= current_time)
        {
            if (current_time < processes[number_of_processes].state.size())
                processes[number_of_processes].state.at(current_time) = 0;
            ready_queue.push(&processes[number_of_processes]);
            number_of_processes++;
        }

        // If the ready queue is empty, advance time
        if (ready_queue.empty())
        {
            cout<<"f";
            current_time++;
            continue;
        }

        // Find the process with the shortest remaining time
        min_burst = INT_MAX;
        while (!ready_queue.empty())
        {
            Process *temp_process = ready_queue.front();
            ready_queue.pop();
            temp_queue.push(temp_process);

            if (temp_process->serviceTime < min_burst)
            {
                min_burst = temp_process->serviceTime;
                min_process = temp_process;
            }
        }

        // Rebuild the ready queue (except the process with the shortest burst time)
        while (!temp_queue.empty())
        {
            Process *temp_process = temp_queue.front();
            temp_queue.pop();
            if (temp_process != min_process)
            {
                ready_queue.push(temp_process);
            }
            
        }

        // Execute the selected process
        if (min_process)
        {
            min_process->remainingTime--;
            current_time++;
            min_process->state[current_time]=1;

            if (min_process->remainingTime == 0)
            {
                min_process->finishTime = current_time;
            }
            else
            {
                ready_queue.push(min_process);
            }
        }
    }
}

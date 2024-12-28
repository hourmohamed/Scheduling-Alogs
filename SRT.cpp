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
    Process *min_process = nullptr;
    std::queue<Process *> ready_queue; // Explicit ready queue

    // Sort processes by arrival time
    sort_by_arrival(processes);

    while (number_of_processes < processes.size() || !ready_queue.empty())
    {
        // Add processes that have arrived to the ready queue
        while (number_of_processes < processes.size() && processes[number_of_processes].arrivalTime <= current_time)
        {
            ready_queue.push(&processes[number_of_processes]);
            processes[number_of_processes].state[current_time] = 0; // Mark as ready
            // cout << "Process " << processes[number_of_processes].name
            //      << " entered ready queue at time " << current_time << endl;
            number_of_processes++;
        }

        // If the ready queue is empty, advance time to the next arrival
        if (ready_queue.empty())
        {
            if (number_of_processes < processes.size())
            {
                current_time = processes[number_of_processes].arrivalTime; // Jump to the next process arrival time
                //cout << "No process in ready queue. Advancing time to " << current_time << endl;
            }
            continue;
        }

        // Find the process with the shortest remaining time
        min_process = nullptr;
        std::queue<Process *> temp_queue;

        while (!ready_queue.empty())
        {
            Process *temp_process = ready_queue.front();
            ready_queue.pop();

            if (temp_process->remainingTime > 0 &&
                (min_process == nullptr || temp_process->remainingTime < min_process->remainingTime))
            {
                min_process = temp_process;
            }

            temp_queue.push(temp_process);
        }

        // Rebuild the ready queue
        while (!temp_queue.empty())
        {
            Process *temp_process = temp_queue.front();
            temp_queue.pop();

            // Only re-add processes with remaining time greater than 0
            if (temp_process!=min_process)
            {
                ready_queue.push(temp_process);
                temp_process->state[current_time]=0;
            }
        }

        // Execute the selected process
        if (min_process)
        {
            // cout << "Executing process " << min_process->name
            //      << " at time " << current_time << endl;

            min_process->remainingTime--;
            min_process->state[current_time] = 1; // Mark as executing
            current_time++;                       // Advance time

            if (min_process->remainingTime == 0)
            {
                min_process->finishTime = current_time;
                // cout << "Process " << min_process->name
                //      << " finished at time " << min_process->finishTime << endl;
            }
            else 
            {
                ready_queue.push(min_process);
                //min_process->state[current_time] = 0; 

            }
        }

        // Debug: Print queue status
        //cout << "Ready queue size: " << ready_queue.size() << endl;
    }

    //cout << "Scheduling completed!" << endl;
}



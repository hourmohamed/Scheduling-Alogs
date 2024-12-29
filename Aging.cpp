#include "Aging.h"
#include <iostream>
#include <algorithm>
#include <queue>
#include <climits>
using namespace std;

void Aging::sort_by_arrival(std::vector<Process> &processes)
{
    std::sort(processes.begin(), processes.end(), [](const Process &a, const Process &b)
              { return a.arrivalTime < b.arrivalTime; });
}

std::vector<int> Aging::calculate_finish_times(std::vector<Process> &processes)
{
    vector<int> finish_times;
    for (const auto &process : processes)
    {
        finish_times.push_back(process.finishTime);
    }
    return finish_times;
}

void Aging::schedule(std::vector<Process> &processes)
{
    int current_time = 0;
    int number_of_processes = 0;
    int quantum = this->quantum;

    // Comparator for the priority queue
    auto cmp = [](const Process *a, const Process *b) {
        return a->priority < b->priority;
    };

    std::priority_queue<Process *, std::vector<Process *>, decltype(cmp)> ready_queue(cmp);

    // Sort processes by arrival time
    sort_by_arrival(processes);

    // Main scheduling loop
    while (number_of_processes < processes.size() || !ready_queue.empty())
    {
        // Add arrived processes to the ready queue
        while (number_of_processes < processes.size() && processes[number_of_processes].arrivalTime <= current_time)
        {
            ready_queue.push(&processes[number_of_processes]);
            processes[number_of_processes].priority = processes[number_of_processes].serviceTime; // Assign initial priority (based on service time)
            number_of_processes++;
        }

        // If no processes are ready, advance time
        if (ready_queue.empty())
        {
            current_time+=quantum;
            continue;
        }

        // Execute the highest-priority process
        Process *current_process = ready_queue.top();
        ready_queue.pop();

        int execution_time = min(current_process->remainingTime, quantum); // Execute the process for up to the quantum time
        current_process->remainingTime -= execution_time;

        // Update state for each unit of execution time
        for (int t = 0; t < execution_time; t++)
        {
            if (current_time < this->time_line)
                current_process->state[current_time] = 1; // Mark this time slot as running (1 for running)
            current_time++;
        }

        // If the process is completed, set its finish time
        if (current_process->remainingTime == 0)
        {
            current_process->finishTime = current_time;
        }
        else
        {
            ready_queue.push(current_process); // Re-add to the queue if not finished
        }

        // Increment the priority of all other ready processes (Aging)
        std::vector<Process *> temp_queue;
        while (!ready_queue.empty())
        {
            Process *temp_process = ready_queue.top();
            ready_queue.pop();
            temp_process->priority++; // Aging: increase priority
            temp_queue.push_back(temp_process);
        }

        // Re-add aged processes back to the ready queue
        for (Process *temp_process : temp_queue)
        {
            ready_queue.push(temp_process);
        }

        // Check if the scheduling exceeds the timeline
        if (current_time >= this->time_line)
            break;
    }

}

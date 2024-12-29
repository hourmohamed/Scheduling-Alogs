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

void Aging::schedule(std::vector<Process> &processes, int last_instant)
{
    int current_time = 0;
    int number_of_processes = 0;
    int quantum = this->quantum;

    // Comparator for the priority queue
    auto cmp = [](const Process *a, const Process *b)
    {
        return a->priority < b->priority;
    };
    queue<Process *> ready_queue;
    queue<Process *> temp_queue;
    // std::priority_queue<Process *, std::vector<Process *>, decltype(cmp)> ready_queue(cmp);

    // Sort processes by arrival time
    sort_by_arrival(processes);

    // Main scheduling loop
    while (number_of_processes < processes.size() || !ready_queue.empty())
    {

        while (number_of_processes < processes.size() && processes[number_of_processes].arrivalTime <= current_time)
        {
            ready_queue.push(&processes[number_of_processes]);
            processes[number_of_processes].priority = processes[number_of_processes].serviceTime;
            number_of_processes++;
        }

        if (ready_queue.empty())
        {
            current_time += quantum;
            continue;
        }
        Process *current_process;
        Process *max_process;
        current_process = ready_queue.front();
        ready_queue.pop();
        temp_queue.push(current_process);
        // cout<<current_process->name<<current_process->priority<<" ";
        int max_priority = current_process->priority;
        while (!ready_queue.empty())
        {
            current_process = ready_queue.front();
            ready_queue.pop();

            if (current_process->priority > max_priority)
            {
                max_priority = current_process->priority;
                // max_process=current_process;
            }
            temp_queue.push(current_process);
        }
        bool first_process = false;
        while (!temp_queue.empty())
        {
            current_process = temp_queue.front();
            temp_queue.pop();
            if (current_process->priority == max_priority)
            {
                if (!first_process)
                {
                    max_process = current_process;
                    first_process = true;
                    continue;
                }
                
            }
            ready_queue.push(current_process);
        }

        int execution_time = quantum;
        // max_process->remainingTime -= execution_time;
        cout << max_process->name << max_process->priority << " ";
        cout << endl;

        for (int t = 0; t < execution_time; t++)
        {
            if (current_time < this->time_line)
                max_process->state[current_time] = 1;
            current_time++;
        }

        std::vector<Process *> temp_queue;
        while (!ready_queue.empty())
        {
            Process *temp_process = ready_queue.front();
            ready_queue.pop();
            temp_process->priority++;
            temp_queue.push_back(temp_process);
        }

        for (Process *temp_process : temp_queue)
        {
            ready_queue.push(temp_process);
        }
        ready_queue.push(max_process);
        // cout<<max_process->name<<max_process->priority<<endl;
        if (current_time >= this->time_line)
            break;
        cout << ready_queue.size() << endl;
    }
}

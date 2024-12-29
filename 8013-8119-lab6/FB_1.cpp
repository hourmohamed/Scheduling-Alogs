#include "FB_1.h"
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

void FB_1::sort_by_arrival(std::vector<Process> &processes)
{
    std::sort(processes.begin(), processes.end(), [](const Process &a, const Process &b)
              { return a.arrivalTime < b.arrivalTime; });
}

std::vector<int> FB_1::calculate_finish_times(std::vector<Process> &processes)
{

    vector<int> finish_times;
    for (int i = 0; i < processes.size(); i++)
    {
        finish_times.push_back(processes[i].finishTime);
    }
    return finish_times;
}
bool is_empty_queues(queue<Process *> ready_queues[], int n)
{
    for (int i = 0; i < n; i++)
        if (!ready_queues[i].empty())
            return false;
    return true;
}

void FB_1::schedule(std::vector<Process> &processes, int last_instant)
{
    int current_time = 0;
    int number_of_processes = 0;
    queue<Process *> ready_queues[processes.size()];

    sort_by_arrival(processes);

    while (number_of_processes < processes.size() || !is_empty_queues(ready_queues, processes.size()))
    {

        while (number_of_processes < processes.size() && processes[number_of_processes].arrivalTime <= current_time)
        {
            ready_queues[0].push(&processes[number_of_processes]);
            processes[number_of_processes].state[current_time] = 0;
            number_of_processes++;
        }

        if (is_empty_queues(ready_queues, processes.size()))
        {
            if (number_of_processes < processes.size())
            {
                current_time = processes[number_of_processes].arrivalTime;
            }
            continue;
        }

        Process *current_process = nullptr;
        int current_queue = -1;
        for (int i = 0; i < processes.size(); i++)
        {
            if (!ready_queues[i].empty())
            {
                current_process = ready_queues[i].front();
                ready_queues[i].pop();
                current_queue = i;
                // cout << current_process->name << " is executing now " << current_queue << endl;
                break;
            }
        }
        for (int i = 0; i < processes.size(); i++)
        {
            if (i!=processes[i].priority&&processes[i].arrivalTime<=current_time &&processes[i].remainingTime!=0)
                processes[i].state[current_time]=0;
        }

        current_process->state[current_time] = 1;
        current_time++;
        current_process->remainingTime--;

        if (current_process->remainingTime == 0)
        {
            current_process->finishTime = current_time;
        }
        else
        {

            if (!is_empty_queues(ready_queues, processes.size()))
            {

                int next_queue = std::min(current_queue + 1, (int)processes.size() - 1);
                ready_queues[next_queue].push(current_process);
                // cout << current_process->name << " is moving to lowest queue  " << next_queue << endl;
            }
            else
            {
                // Process stays in its current queue
                while (number_of_processes < processes.size() && processes[number_of_processes].arrivalTime <= current_time)
                {
                    ready_queues[0].push(&processes[number_of_processes]);
                    processes[number_of_processes].state[current_time] = 0;
                    number_of_processes++;
                }
                ready_queues[current_queue].push(current_process);
                // cout << current_process->name << " is moving to same queue  " << current_queue << endl;
            }
        }
    }
}

// push awel mara fy awel queue
//  law lesa makhlstsh push fy el next queue
//  law khalast dispatch
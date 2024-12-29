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

    std::vector<Process *> ready_queue;

    
    sort_by_arrival(processes);

 
    while (current_time < this->time_line)
    {
        
        while (number_of_processes < processes.size() && processes[number_of_processes].arrivalTime <= current_time)
        {
            ready_queue.push_back(&processes[number_of_processes]);
            for (int j = processes[number_of_processes].arrivalTime; j <= current_time; ++j)
                processes[number_of_processes].state.at(j) = 0;
            //processes[number_of_processes].state.at(current_time) = 0;
            number_of_processes++;
        }

        if (ready_queue.empty())
        {
            // No process ready, increment time
            current_time+=quantum;
            continue;
        }

       
        std::sort(ready_queue.begin(), ready_queue.end(),
                  [](const Process *a, const Process *b) {
                      return a->priority > b->priority ||
                             (a->priority == b->priority && a->arrivalTime < b->arrivalTime);
                  });

        // Select the highest priority process
        Process *max_process = ready_queue.front();
        ready_queue.erase(ready_queue.begin()); // Remove from ready queue

        // Execute the chosen process for one quantum
        cout << "Executing process: " << max_process->name
             << " (Priority: " << max_process->priority << ") at time " << current_time << endl;

        for (int t = 0; t < quantum; t++)
        {
            if (current_time < this->time_line)
                max_process->state.at(current_time) = 1;

            current_time++;
        }

        // Aging: Increment priority for waiting processes only
        for (Process *waiting_process : ready_queue)
        {
            waiting_process->priority++; // Increase priority due to aging
        }

        // Reinsert the executed process into the ready queue
        ready_queue.push_back(max_process);

        // Add newly arriving processes
        while (number_of_processes < processes.size() && processes[number_of_processes].arrivalTime <= current_time)
        {
            for (int j = processes[number_of_processes].arrivalTime; j < current_time; ++j)
                processes[number_of_processes].state.at(j) = 0;

            ready_queue.push_back(&processes[number_of_processes]);
            number_of_processes++;
        }

        // Break the loop if the timeline is reached
        if (current_time >= this->time_line)
            break;
    }
}





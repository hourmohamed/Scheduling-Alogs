#include "Aging.h"
#include <iostream>
#include <algorithm>
#include <queue>
#include <climits>
using namespace std;

void Aging::sort_by_arrival(std::vector<Process> &processes) {
    std::sort(processes.begin(), processes.end(), [](const Process &a, const Process &b) {
        return a.arrivalTime < b.arrivalTime;
    });
}

std::vector<int> Aging::calculate_finish_times(std::vector<Process> &processes) {
    vector<int> finish_times;
    for (const auto &process : processes) {
        finish_times.push_back(process.finishTime);
    }
    return finish_times;
}

void Aging::schedule(std::vector<Process> &processes, int last_instant) {
    int current_time = 0;
    int quantum = this->quantum;
    queue<Process*> ready_queue;
    int number=0;
    // Store initial priorities
    vector<int> initial_priorities;
    for (const auto &process : processes) {
        initial_priorities.push_back(process.priority);
    }

    while (current_time < this->time_line) {
        // Check for newly arrived processes
        while (number < processes.size() && processes[number].arrivalTime <= current_time)
        {
            for (int j = processes[number].arrivalTime; j < current_time; ++j)
                processes[number].state.at(j) = 0;
            processes[number].state.at(current_time) = 0;
            ready_queue.push(&processes[number]);
            number++;
        }

        // Mark all processes in ready queue with state 0
        
        queue<Process*> temp_ready = ready_queue;
        while (!temp_ready.empty()) {
            Process* p = temp_ready.front();
            p->state[current_time] = 0;  // Set state to 0 for waiting processes
            temp_ready.pop();
        }

        if (ready_queue.empty()) {
            current_time+quantum;
            continue;
        }

        // Find process with highest priority
        Process* highest_priority_process = nullptr;
        int max_priority = -1;
        queue<Process*> temp_queue;

        while (!ready_queue.empty()) {
            Process* current = ready_queue.front();
            ready_queue.pop();
            
            if (current->priority > max_priority) {
                if (highest_priority_process) {
                    temp_queue.push(highest_priority_process);
                }
                highest_priority_process = current;
                max_priority = current->priority;
            } else {
                temp_queue.push(current);
            }
        }

        // Execute highest priority process
        if (highest_priority_process && current_time < this->time_line) {
            // Execute for quantum time units
            for (int i = 0; i < quantum && current_time < this->time_line; i++) {
                highest_priority_process->state[current_time] = 1;
                
                // Mark all other processes in temp_queue as waiting (state 0)
                queue<Process*> mark_queue = temp_queue;
                while (!mark_queue.empty()) {
                    Process* waiting = mark_queue.front();
                    waiting->state[current_time] = 0;
                    mark_queue.pop();
                }
                
                current_time++;
            }

            size_t process_index = highest_priority_process - &processes[0];
            highest_priority_process->priority = initial_priorities[process_index];

            while (!temp_queue.empty()) {
                Process* waiting = temp_queue.front();
                temp_queue.pop();
                waiting->priority++;
                ready_queue.push(waiting);
            }
           while (number < processes.size() && processes[number].arrivalTime <= current_time)
        {
            for (int j = processes[number].arrivalTime; j < current_time; ++j)
                processes[number].state.at(j) = 0;
            processes[number].state.at(current_time) = 0;
            ready_queue.push(&processes[number]);
            number++;
        }
            ready_queue.push(highest_priority_process);
        }
    }
}
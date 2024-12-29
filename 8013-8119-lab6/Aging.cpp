#include "Aging.h"
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

void Aging::sort_by_arrival(std::vector<Process> &processes) {
    std::sort(processes.begin(), processes.end(), 
        [](const Process &a, const Process &b) {
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
    
    // Store initial priorities and waiting times
    vector<int> initial_priorities;
    vector<int> wait_times(processes.size(), 0);
    
    for (const auto &process : processes) {
        initial_priorities.push_back(process.priority);
    }
    
    while (current_time < this->time_line) {
        // Check for newly arrived processes
        for (size_t i = 0; i < processes.size(); i++) {
            if (processes[i].arrivalTime == current_time) {
                ready_queue.push(&processes[i]);
                processes[i].priority = initial_priorities[i];
            }
        }
        
        if (ready_queue.empty()) {
            current_time++;
            continue;
        }
        
        // Update waiting times and priorities for all processes in ready queue
        queue<Process*> temp_ready = ready_queue;
        while (!temp_ready.empty()) {
            Process* p = temp_ready.front();
            size_t idx = p - &processes[0];
            p->state[current_time] = 0;  // Set state to 0 for waiting processes
            wait_times[idx]++;
            // Increase priority based on waiting time
            p->priority = initial_priorities[idx] + wait_times[idx];
            temp_ready.pop();
        }
        
        // Find process with highest priority
        Process* highest_priority_process = nullptr;
        int max_priority = -1;
        queue<Process*> temp_queue;
        
        // Create a copy of ready_queue for priority comparison
        queue<Process*> priority_queue = ready_queue;
        while (!ready_queue.empty()) {
            ready_queue.pop();
        }
        
        while (!priority_queue.empty()) {
            Process* current = priority_queue.front();
            priority_queue.pop();
            
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
        if (highest_priority_process) {
            size_t process_index = highest_priority_process - &processes[0];
            
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
                if (current_time >= this->time_line) break;
            }
            
            // Reset wait time for executed process
            wait_times[process_index] = 0;
            highest_priority_process->priority = initial_priorities[process_index];
            
            // Add processes back to ready queue
            while (!temp_queue.empty()) {
                Process* waiting = temp_queue.front();
                temp_queue.pop();
                ready_queue.push(waiting);
            }
            ready_queue.push(highest_priority_process);
        }
    }
}
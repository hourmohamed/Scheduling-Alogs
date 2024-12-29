#include "HRRN.h"
#include <algorithm>
#include <vector>
#include <iostream>

std::vector<int> HRRN::calculate_finish_times(std::vector<Process>& processes) {
    vector<int> finish_times;
    for (int i = 0; i < processes.size(); i++)
    {
        finish_times.push_back(processes[i].finishTime);
    }
    return finish_times;
}

void HRRN::schedule(std::vector<Process>& processes, int last_instant) {
    std::cerr << "in schedule" << std::endl;

    int current_time = 0;
    int completed_count = 0;
    std::vector<bool> completed(processes.size(), false);

    while (completed_count < processes.size()) {
    
        int max_index = -1;
        double max_ratio = -1.0;

        // Find the process with the highest response ratio
        for (size_t i = 0; i < processes.size(); ++i) {
            if (!completed[i] && processes[i].arrivalTime <= current_time) {
                int waiting_time = std::max(0, current_time - processes[i].arrivalTime);
                double response_ratio = (waiting_time + processes[i].serviceTime) / (double)processes[i].serviceTime;

                if (response_ratio > max_ratio) {
                    max_ratio = response_ratio;
                    max_index = i;
                }
            }
        }

        if (max_index != -1) {
            Process& selected_process = processes[max_index];
            current_time = std::max(current_time, selected_process.arrivalTime);

            
            
            for (int t = selected_process.arrivalTime; t < current_time; ++t) {
                int wrapped_time = t % this->time_line;  
                selected_process.state[wrapped_time] = 0;  
            }

            
            current_time = std::max(current_time, selected_process.arrivalTime);

          
            for (int t = current_time; t < current_time + selected_process.serviceTime; ++t) {
                int wrapped_time = t % this->time_line;  
                selected_process.state[wrapped_time] = 1; 
            }

            // std::cerr << "heeeeeeeeeeeerrrrrrrrrrrrrrrrrrrrreeeeeeeeeeeeeeeeeeee" << std::endl;
            selected_process.finishTime = current_time + selected_process.serviceTime;
            selected_process.turnAroundTime = selected_process.finishTime - selected_process.arrivalTime;
            // std::cerr << "Turnaround for: " << selected_process.name << " is " << selected_process.turnAroundTime << std::endl;

            
            current_time = selected_process.finishTime;
            completed[max_index] = true;
            completed_count++;
        } else {
            
            std::cout << "No process ready; incrementing time to " << (current_time + 1) << std::endl;
            current_time++;
        }
    }

   
}

#include "HRRN.h"
#include <algorithm>
#include <vector>
#include <iostream>

std::vector<int> HRRN::calculate_finish_times(std::vector<Process>& processes) {
    int current_time = 0;
    std::vector<int> finish_times;

    for (auto& p : processes) {
        if (p.arrivalTime > current_time) {
            current_time = p.arrivalTime;
        }
        p.finishTime = current_time + p.serviceTime;
        current_time = p.finishTime;
        finish_times.push_back(p.finishTime);
    }

    return finish_times;
}


 void HRRN::schedule(std::vector<Process>& processes) {
    int current_time = 0;
    int completed_count = 0;
    std::vector<bool> completed(processes.size(), false);

    while (completed_count < processes.size()) {
        int max_index = -1;
        double max_ratio = -1.0;

        
      for (size_t i = 0; i < processes.size(); ++i) {
    if (!completed[i] && processes[i].arrivalTime <= current_time) {
        int waiting_time = std::max(0, current_time - processes[i].arrivalTime);
        double response_ratio = (waiting_time + processes[i].serviceTime) / (double)processes[i].serviceTime;

        std::cerr << "Process " << processes[i].name
                  << " | Arrival Time: " << processes[i].arrivalTime 
                  << " | Service Time: " << processes[i].serviceTime 
                  << " | Waiting Time: " << waiting_time 
                  << " | Response Ratio: " << response_ratio 
                  << " | Current Time: " << current_time << std::endl;

        if (response_ratio > max_ratio) {
            max_ratio = response_ratio;
            max_index = i;
        }
    }
}

        if (max_index != -1) {
          
            Process& selected_process = processes[max_index];
            current_time = std::max(current_time, selected_process.arrivalTime);
            selected_process.finishTime = current_time + selected_process.serviceTime;
            // selected_process.waitingTime = current_time - selected_process.arrivalTime;

           
            std::cout << "Executing process " << max_index << " at time " << current_time << std::endl;
            current_time = selected_process.finishTime;
            completed[max_index] = true;
            completed_count++;
        } else {
          
            std::cout << "No process ready; incrementing time to " << (current_time + 1) << std::endl;
            current_time++;
        }
    }
}

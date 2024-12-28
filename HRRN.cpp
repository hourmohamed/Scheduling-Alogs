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

void HRRN::schedule(std::vector<Process>& processes) {
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

            // Mark the process as running by updating its state
            for (int t = current_time; t < current_time + selected_process.serviceTime; ++t) {
                if (t >= selected_process.state.size()) {
                    selected_process.state.resize(t + 1, 0);
                }
                selected_process.state[t] = 1; // Process is running
            }

            // Update process timings
            selected_process.finishTime = current_time + selected_process.serviceTime;
            selected_process.turnAroundTime = selected_process.finishTime - selected_process.arrivalTime;
            std::cerr << "Turnaround for: " << selected_process.name << " is " << selected_process.turnAroundTime << std::endl;

            current_time = selected_process.finishTime;
            completed[max_index] = true;
            completed_count++;
        } else {
            // If no process is ready, increment time
            std::cout << "No process ready; incrementing time to " << (current_time + 1) << std::endl;
            current_time++;
        }
    }

    // Debug: Print turnaround times
    for (int i = 0; i < processes.size(); i++) {
        std::cerr << "Turnaround times: " << processes[i].turnAroundTime << " " << processes[i].name << std::endl;
    }
}

#include "FCFS.h"
#include <iostream>
#include <algorithm>

// Sort the processes by arrival time in ascending order
// void FCFS::sort_by_arrival(std::vector<Process>& processes) {
//     std::sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
//         return a.arrivalTime < b.arrivalTime;
//     });
// }

// Calculate finish times for each process in FCFS
std::vector<int> FCFS::calculate_finish_times(std::vector<Process>& processes) {
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

// Main FCFS scheduling function
// void FCFS::schedule(std::vector<Process>& processes) {
   

// if (processes.empty()) {
//     std::cerr << "Error: No processes to schedule!" << std::endl;
//     return;
// }


// sort_by_arrival(processes);


//  // Sort the processes by arrival time

//     std::vector<int> finish_times = calculate_finish_times(processes);  // Get finish times
//     std::vector<int> turnaround_times = calculate_turnaround(processes);  // Get turnaround times
//     std::vector<double> normTurn_times = calculate_normturn(processes);  // Get normalized turnaround times

//     // Update processes with calculated times
//     for (int i = 0; i < processes.size(); ++i) {
//         processes[i].finishTime = finish_times[i];
//         processes[i].turnAroundTime = turnaround_times[i];
//         processes[i].normTurn = normTurn_times[i];
//     }
// }

void FCFS::schedule(std::vector<Process>& processes) {
    if (processes.empty()) {
        std::cerr << "Error: No processes to schedule!" << std::endl;
        return;
    }

    
    sort_by_arrival(processes);

   
    std::vector<int> finish_times = calculate_finish_times(processes);
    std::vector<int> turnaround_times = calculate_turnaround(processes);
    std::vector<double> normTurn_times = calculate_normturn(processes);

  
    for (int i = 0; i < processes.size(); ++i) {
        // std::cerr << "in loop 1" << std::endl;
        processes[i].finishTime = finish_times[i];
        processes[i].turnAroundTime = turnaround_times[i];
        processes[i].normTurn = normTurn_times[i];
    }

    int current_time = 0;

  
    for (auto& p : processes) {
        // std::cerr << "in loop 2" << std::endl;
         
        for (int t = p.arrivalTime; t < current_time; ++t) {
            std::cerr << "in loop 3" << std::endl;
            int wrapped_time = t % this->time_line;
            p.state[wrapped_time] = 0;  // Waiting (dot)
            std::cerr << p.name << std::endl;
            // std::cerr << wrapped_time << std::endl;
            // std::cerr << current_time << std::endl;
        }

        
        current_time = std::max(current_time, p.arrivalTime);

       
        for (int t = current_time; t < p.finishTime; ++t) {
            int wrapped_time = t % this->time_line;
            p.state[wrapped_time] = 1; 
        }

      
        current_time = p.finishTime;
        for (int t = current_time; t < this->time_line; ++t) {
            int wrapped_time = t % this->time_line;
            if (p.state[wrapped_time] != 1) {  
                p.state[wrapped_time] = -1;  
            }
        }
    }
}

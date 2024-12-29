#include "SPN.h"
#include <iostream>
#include <algorithm>
#include <queue>

#include <climits>
#include <iostream>
#include <vector>


std::vector<int> SPN::calculate_finish_times(std::vector<Process>& processes){
        vector <int> finish_times;
    for (int i=0;i<processes.size();i++)
    {
        finish_times.push_back(processes[i].finishTime);
    }
    return finish_times;

}


struct CompareServiceTime {
    bool operator()(const Process* p1, const Process* p2) const {
        return p1->serviceTime > p2->serviceTime; 
    }
};




// void SPN::schedule(std::vector<Process>& processes) {

//     if (processes.empty()) {
//     std::cerr << "Error: No processes to schedule!" << std::endl;
//     return;
// }
//         sort_by_arrival(processes);

//         std::priority_queue<Process* , std::vector<Process*>, CompareServiceTime> pq;
//         int currentTime = 0;
//         int index = 0; 

//         std::vector<Process> completedProcesses;
//         while (index < processes.size() || !pq.empty()) {
//             while (index < processes.size() && processes[index].arrivalTime <= currentTime) {
                
//                 pq.push(& processes[index]);
//                 index++;
//             }
//             if (!pq.empty()) {
              
//                 Process* current = pq.top();
//                 pq.pop();
//                 current->state[currentTime] = 1;

                          
//                 currentTime += current->serviceTime;
//                 current->finishTime = currentTime;
               
//                 completedProcesses.push_back(*current);

//             } else {
//                 currentTime = processes[index].arrivalTime;
//             }
//         }

//     for(int i = 0; i<processes.size(); i++)
//     {
//         processes[i].turnAroundTime = processes[i].finishTime-processes[i].arrivalTime; 
//         double normturn = static_cast<double> (processes[i].turnAroundTime)/processes[i].serviceTime;
//         processes[i].normTurn = normturn;
//     }
  


// }

void SPN::schedule(std::vector<Process>& processes, int last_instant) {
    if (processes.empty()) {
        std::cerr << "Error: No processes to schedule!" << std::endl;
        return;
    }

    std::sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.arrivalTime < b.arrivalTime;
    });

    int current_time = 0;
    std::vector<bool> completed(processes.size(), false);
    int completed_count = 0;

  
    while (completed_count < processes.size()) {
        
        int shortest_idx = -1;
        int shortest_time = INT_MAX;

        
        for (int i = 0; i < processes.size(); ++i) {
            // std::cerr << "inloop" << std::endl;
            if (!completed[i] && processes[i].arrivalTime <= current_time &&
                processes[i].serviceTime < shortest_time) {
                shortest_time = processes[i].serviceTime;
                shortest_idx = i;
            }
        }

        
        if (shortest_idx == -1) {
            for (auto& p : processes) {
                if (!completed[&p - &processes[0]] && p.arrivalTime <= current_time) {
                    int wrapped_time = current_time % this->time_line;
                    p.state[wrapped_time] = 5; 
                }
            }
            current_time++;
            continue;
        }

       
        Process& p = processes[shortest_idx];

        
        for (int t = p.arrivalTime; t < current_time; ++t) {
            int wrapped_time = t % this->time_line;
            p.state[wrapped_time] = 0; 
        }

     
        current_time = std::max(current_time, p.arrivalTime);
        for (int t = current_time; t < current_time + p.serviceTime; ++t) {
            int wrapped_time = t % this->time_line;
            p.state[wrapped_time] = 1; 
        }

       
        p.finishTime = current_time + p.serviceTime;
        completed[shortest_idx] = true;
        completed_count++;


        current_time = p.finishTime;
    }

    
    for (auto& p : processes) {
        for (int t = current_time; t < this->time_line; ++t) {
            int wrapped_time = t % this->time_line;
            if (p.state[wrapped_time] != 1) {
                p.state[wrapped_time] = -1;  
            }
        }
    }
}

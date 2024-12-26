#include "RoundRobin.h"
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

void RoundRobin::sort_by_arrival(std::vector<Process> &processes)
{
    std::sort(processes.begin(), processes.end(), [](const Process &a, const Process &b)
              { return a.arrivalTime < b.arrivalTime; });
}


std::vector<int> RoundRobin::calculate_finish_times(std::vector<Process> &processes)
{
  
   

    vector <int> finish_times;
    for (int i=0;i<processes.size();i++)
    {
        finish_times.push_back(processes[i].finishTime);
    }
    return finish_times;
}

void RoundRobin::schedule(std::vector<Process> &processes)
{
    int current_time = 0; 
    int number_of_processes = 0;       
    std::queue<Process *> ready_queue;

   
    sort_by_arrival(processes);

    while (number_of_processes < processes.size() || !ready_queue.empty())
    {
      
        while (number_of_processes < processes.size() && processes[number_of_processes].arrivalTime <= current_time)
        {

            processes[number_of_processes].state[current_time]=0;
            ready_queue.push(&processes[number_of_processes]);
            number_of_processes++;
        }

        if (ready_queue.empty()) {
            // No process to execute, mark idle time
            if (number_of_processes < processes.size()) {
                for (int i = current_time; i < processes[number_of_processes].arrivalTime; i++) {
                    // Mark all processes as idle during this time
                    for (auto &process : processes) {
                        process.state[i] = -1; // Assuming -1 denotes idle
                    }
                }
                current_time = processes[number_of_processes].arrivalTime;
            }
            continue;
        }

        Process *current_process = ready_queue.front();
        ready_queue.pop();

        int time_slice = std::min(this->quantum, current_process->remainingTime);
        current_time += time_slice;
        current_process->remainingTime -= time_slice;
        //cout <<current_time<<time_slice<<endl;
        for (int i=current_time-time_slice;i<current_time;i++)
            {
                current_process->state[i]=1;
                //cout <<current_process->name<<" "<<current_process->state[i]<<" "<<i<<endl;
            }
        if (current_process->remainingTime == 0)
        {
            current_process->finishTime = current_time;
            current_process->turnAroundTime = current_process->finishTime - current_process->arrivalTime;
            current_process->normTurn = static_cast<double>(current_process->turnAroundTime) / current_process->serviceTime;
            // cout<<current_process->name<<" finished executing "<<current_process->finishTime<<" "
            // <<current_process->arrivalTime<<" "<<current_process->turnAroundTime<<endl;
        }
        else
        {
            while (number_of_processes < processes.size() && processes[number_of_processes].arrivalTime <= current_time)
            {

                processes[number_of_processes].state[current_time]=0;
                ready_queue.push(&processes[number_of_processes]);
                number_of_processes++;
            }
            
            ready_queue.push(current_process);
        }
        //cout <<"ana hena";
    }
    //cerr <<"done scheduling";
}

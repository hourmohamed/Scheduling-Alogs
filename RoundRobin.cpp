// #include "RoundRobin.h"
// #include <iostream>
// #include <algorithm>
// #include <queue>
// using namespace std;
// // Sort the processes by arrival time in ascending order
// void RoundRobin::sort_by_arrival(std::vector<Process> &processes)
// {
//     std::sort(processes.begin(), processes.end(), [](const Process &a, const Process &b)
//               { return a.arrivalTime < b.arrivalTime; });
// }

// // Calculate finish times for each process in RoundRobin
// std::vector<int> RoundRobin::calculate_finish_times(std::vector<Process> &processes)
// {

//     // return finish_times;
//     vector<int> finish_times;
//     for (int i = 0; i < processes.size(); i++)
//     {
//         finish_times.push_back(processes[i].finishTime);
//     }
//     return finish_times;
// }
// void RoundRobin::schedule(std::vector<Process> &processes)
// {
//     int current_time = 0;
//     int number_of_processes = 0;
//     std::queue<Process *> ready_queue;

//     sort_by_arrival(processes);

//     while (number_of_processes < processes.size() || !ready_queue.empty())
//     {

//         while (number_of_processes < processes.size() && processes[number_of_processes].arrivalTime <= current_time)
//         {
//             processes[number_of_processes].state.at(current_time) = 0;
//             ready_queue.push(&processes[number_of_processes]);
//             number_of_processes++;
//             //cerr<<"here";
//         }

//         if (ready_queue.empty())
//         {
//             current_time = processes[number_of_processes].arrivalTime;
//             continue;
//         }

//         Process *current_process = ready_queue.front();
//         ready_queue.pop();

//         int time_slice = std::min(this->quantum, current_process->remainingTime);
//         for (int n=0;n<processes.size();n++)
//             for (int i = current_time; i <= current_time + time_slice; i++)
//                 if (processes[n].arrivalTime<=i&&!processes[n].done)
//                     processes[n].state[i]=-1;

//         current_time += time_slice;
//         current_process->remainingTime -= time_slice;

//         // Ensure we're updating the correct process state
//         for (int i = current_time - time_slice; i <current_time; ++i)
//             current_process->state.at(i) = 1; // Update state for current process

//         for (int i = 0; i < processes.size(); i++)
//             if (&processes[i] != current_process && processes[i].remainingTime > 0 && processes[i].arrivalTime<=current_time)

//         if (current_process->remainingTime == 0)
//         {
//             current_process->finishTime = current_time;
//             current_process->turnAroundTime = current_process->finishTime - current_process->arrivalTime;
//             current_process->normTurn = static_cast<double>(current_process->turnAroundTime) / current_process->serviceTime;
//             current_process->done=true;
//         }
//         else
//         {
//             // Recheck new processes that arrive at the current time
//             while (number_of_processes < processes.size() && processes[number_of_processes].arrivalTime <= current_time)
//             {
//                 processes[number_of_processes].state.at(current_time) = 0;
//                 ready_queue.push(&processes[number_of_processes]);
//                 number_of_processes++;
//             }

//             ready_queue.push(current_process); // Re-add current process to the queue
//         }
//     }
// }
#include "RoundRobin.h"
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;
// Sort the processes by arrival time in ascending order
void RoundRobin::sort_by_arrival(std::vector<Process> &processes)
{
    std::sort(processes.begin(), processes.end(), [](const Process &a, const Process &b)
              { return a.arrivalTime < b.arrivalTime; });
}

// Calculate finish times for each process in RoundRobin
std::vector<int> RoundRobin::calculate_finish_times(std::vector<Process> &processes)
{

    vector<int> finish_times;
    for (int i = 0; i < processes.size(); i++)
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
            for (int j = processes[number_of_processes].arrivalTime; j < current_time; ++j)
                processes[number_of_processes].state.at(j) = 0;
            processes[number_of_processes].state.at(current_time) = 0;
            ready_queue.push(&processes[number_of_processes]);
            number_of_processes++;
        }

        if (ready_queue.empty())
        {
            current_time = processes[number_of_processes].arrivalTime;
            continue;
        }

        Process *current_process = ready_queue.front();
        ready_queue.pop();

        int time_slice = std::min(this->quantum, current_process->remainingTime);
        // for (int n=0;n<processes.size();n++)
        //     for (int i = current_time; i <= current_time + time_slice; i++)
        //         if (processes[n].arrivalTime<=i&&processes[n].finishTime<i)
        //             processes[n].state[i]=0;
        current_time += time_slice;
        current_process->remainingTime -= time_slice;

        // Ensure we're updating the correct process state
        for (int i = current_time - time_slice; i < current_time; ++i)
            current_process->state.at(i) = 1; // Update state for current process

        for (int i = 0; i < processes.size(); i++)
            if (&processes[i] != current_process && processes[i].remainingTime > 0 && processes[i].arrivalTime <= current_time - time_slice)
                for (int j = current_time - time_slice; j < current_time; ++j)
                    processes[i].state[j] = 0;
        if (current_process->remainingTime == 0)
        {
            current_process->finishTime = current_time;
            current_process->turnAroundTime = current_process->finishTime - current_process->arrivalTime;
            current_process->normTurn = static_cast<double>(current_process->turnAroundTime) / current_process->serviceTime;
            current_process->done = true;
        }
        else
        {
            // Recheck new processes that arrive at the current time
            while (number_of_processes < processes.size() && processes[number_of_processes].arrivalTime <= current_time)
            {
               // cout << processes[number_of_processes].name << processes[number_of_processes].arrivalTime << current_time << time_slice << endl;
                for (int j = processes[number_of_processes].arrivalTime; j < current_time; ++j)
                    processes[number_of_processes].state.at(j) = 0;
                ready_queue.push(&processes[number_of_processes]);
                number_of_processes++;
            }

            ready_queue.push(current_process); // Re-add current process to the queue
        }
    }
}
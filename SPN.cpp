#include "SPN.h"
#include <iostream>
#include <algorithm>
#include <queue>


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
        return p1->serviceTime > p2->serviceTime; // Adjust as needed for your comparison logic
    }
};







void SPN::schedule(std::vector<Process>& processes) {

    if (processes.empty()) {
    std::cerr << "Error: No processes to schedule!" << std::endl;
    return;
}

        // std::cerr << "before sort by arrival" << std::endl;
        sort_by_arrival(processes);
        // std::cerr << "after sort by arrival" << std::endl;


        std::priority_queue<Process* , std::vector<Process*>, CompareServiceTime> pq;
        int currentTime = 0;
        int index = 0; 

        std::vector<Process> completedProcesses;

        while (index < processes.size() || !pq.empty()) {
            while (index < processes.size() && processes[index].arrivalTime <= currentTime) {

                // std::cerr << processes[index].arrivalTime << std::endl;
                // std::cerr << currentTime << std::endl;
                pq.push(& processes[index]);
                index++;
            }

            if (!pq.empty()) {
              
                Process* current = pq.top();
                pq.pop();

                          
                currentTime += current->serviceTime;
                current->finishTime = currentTime;
                
                //  std::cerr << "process: " <<  current.name << std::endl;
                //  std::cerr << "current time: " << currentTime << std::endl;
                //  std::cerr << "finish time: " << current.finishTime << std::endl;
 
               
                completedProcesses.push_back(*current);

            } else {
                currentTime = processes[index].arrivalTime;
            }
        }
 



    
    // std::vector<int> turnaround_times = calculate_turnaround(processes);  
    // std::vector<double> normTurn_times = calculate_normturn(processes); 

    // calc turnaround time
    for(int i = 0; i<processes.size(); i++)
    {
        // std::cerr << "in loop: " << i << std::endl;
        processes[i].turnAroundTime = processes[i].finishTime-processes[i].arrivalTime;
        // std::cerr << processes[i].turnAroundTime << std::endl;
        double normturn = static_cast<double> (processes[i].turnAroundTime)/processes[i].serviceTime;
        processes[i].normTurn = normturn;
        // std::cerr << processes[i].normTurn << std::endl;
        // printf("%2.2f \n", normturn);
    }
  


    // for (int i = 0; i < processes.size(); ++i) {
    //     // processes[i].turnAroundTime = turnaround_times[i];
    //     // processes[i].normTurn = normTurn_times[i];

    //     std::cerr << processes[i].turnAroundTime <<std::endl;
    // }


}
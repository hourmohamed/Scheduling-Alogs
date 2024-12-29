#include "FB2i.h"
#include <queue>
#include <unordered_map>
#include <math.h>



std::vector<int> FB2i::calculate_finish_times(std::vector<Process>& processes){
    vector <int> finish_times;
    for (int i=0;i<processes.size();i++)
    {
        finish_times.push_back(processes[i].finishTime);
    }
    return finish_times;
}


// void FB2i::schedule(std::vector<Process>& processes, int last_instant){
//     // std::cerr << "passes last instant" << last_instant <<std::endl;
//     priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int,int>>> pq;
//     unordered_map<int, int> remaining_service_time;
//     int j=0;

//     if(processes[0].arrivalTime == 0){
//         pq.push(make_pair(0, j));
//         remaining_service_time[j] = processes[j].serviceTime;
//         j++;
//     }

//     // loop on each time block
//     for(int time = 0 ; time < last_instant ; time++){

//         // if there are processes in the pq
//         if(!pq.empty()){
//             int priority_level = pq.top().first;
//             int process_index = pq.top().second;
//             std::cerr << process_index << std::endl;

//             // pop the process with the least quantum
//             pq.pop();
            
//             while(j < processes.size() && processes[j].arrivalTime <= time+1){
//                 pq.push(make_pair(0, j));
//                 remaining_service_time[j] = processes[j].serviceTime;
//                 processes[j].state[time++] = 0;
//                 j++;
                
//             }
//             int current_quantum = pow(2, priority_level);
//             // std::cerr << processes[time].name << " " << std::endl;
//             // std::cerr << current_quantum << std::endl;
//             int temp = time;


//             // process is running until its quantum becomes 0 or it finishes
//             while(current_quantum>0 && remaining_service_time[process_index]>0){
//                 current_quantum --;
//                 remaining_service_time[process_index]--;
//                 processes[process_index].state[temp++] = 1;

//             }

//             if(remaining_service_time[process_index] == 0){
//                 processes[process_index].finishTime = temp;
//                 // std::cerr << processes[process_index].finishTime <<  std::endl;;
//                 processes[process_index].turnAroundTime = processes[process_index].finishTime - processes[process_index].arrivalTime;
//                 processes[process_index].normTurn = processes[process_index].turnAroundTime*1.0/processes[process_index].serviceTime;

//             }
//             else{
//                 if(pq.size()>=1){
//                     pq.push(make_pair(priority_level+1, process_index));

//                 }else{
//                     pq.push(make_pair(priority_level, process_index));
//                 }
                
//             }
            
//             time = temp-1;
//         }
//             while(j<processes.size() && processes[j].arrivalTime <= time+1){
//                 pq.push(make_pair(0, j));
//                 remaining_service_time[j] = processes[j].serviceTime;
//                 j++;
//             }
        
//     }



// }


void FB2i::schedule(std::vector<Process>& processes, int last_instant) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    unordered_map<int, int> remaining_service_time;
    // int last_instant = 
    int j = 0;


    if (processes[0].arrivalTime == 0) {
        pq.push(make_pair(0, j));
        remaining_service_time[j] = processes[j].serviceTime;
        j++;
    }

   
    for (int time = 0; time < last_instant; time++) {

        for(int i=0; i<processes.size(); i++)
        {
            for(int j=0; j<last_instant; j++)
            if (processes[i].state[j] != 1) {
                if(processes[i].arrivalTime < j){
                    processes[i].state[j] = 0; 
                }
            }
        }
        
        if (!pq.empty()) {
            int priority_level = pq.top().first;
            int process_index = pq.top().second;
            int arrival_time = processes[process_index].arrivalTime;
            int service_time = processes[process_index].serviceTime;
            pq.pop();

            
            while (j < processes.size() && processes[j].arrivalTime <= time + 1) {
                // processes[j].state[time] = 0; 
                pq.push(make_pair(0, j));
                remaining_service_time[j] = processes[j].serviceTime;
                 
                j++;
            }

            int current_quantum = pow(2, priority_level);
            int temp = time;

            while (current_quantum > 0 && remaining_service_time[process_index] > 0) {
                current_quantum--;
                remaining_service_time[process_index]--;
                processes[process_index].state[temp++] = 1;
            }

          
            if (remaining_service_time[process_index] == 0) {
                processes[process_index].finishTime = temp;
                processes[process_index].turnAroundTime = processes[process_index].finishTime - arrival_time;
                processes[process_index].normTurn = (processes[process_index].turnAroundTime * 1.0) / service_time;

                


            } else { 
                if (pq.size() >= 1) {
                    pq.push(make_pair(priority_level + 1, process_index));
                } else {
                    pq.push(make_pair(priority_level, process_index));
                }
            }
 
            time = temp - 1;
        }
        // std::cerr << "before last while" << std::endl;
        
 
        
        while (j < processes.size() && processes[j].arrivalTime <= time + 1) {
            std::cerr << "in last while" << std::endl;
            processes[j].state[time] = 0; 
            pq.push(make_pair(0, j));
            remaining_service_time[j] = processes[j].serviceTime;
            j++;
        }
    }
    for(int i = 0 ;i <processes.size();i++)
        {
            int k = processes[i].finishTime;
            for(int j = k ; j<last_instant ; j ++)
            {
                processes[i].state[j] = -1;
            }
        }

}
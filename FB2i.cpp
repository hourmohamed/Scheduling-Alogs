#include "FB2i.h"
#include <queue>
#include <unordered_map>

std::vector<int> FB2i::calculate_finish_times(std::vector<Process>& processes){
    vector <int> finish_times;
    for (int i=0;i<processes.size();i++)
    {
        finish_times.push_back(processes[i].finishTime);
    }
    return finish_times;
}





void FB2i::schedule(std::vector<Process>& processes, int last_instant){
    std::cerr << last_instant <<std::endl;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int,int>>> pq;
    unordered_map<int, int> remaining_service_time;
    int j=0;
    if(processes[0].arrivalTime == 0){
        pq.push(make_pair(0, j));
        remaining_service_time[j] = processes[j].serviceTime;
        j++;
    }

    // for(int time = 0 ; time < i)



}
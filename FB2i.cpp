#include "FB2i.h"
#include <queue>

std::vector<int> FB2i::calculate_finish_times(std::vector<Process>& processes){
    vector <int> finish_times;
    for (int i=0;i<processes.size();i++)
    {
        finish_times.push_back(processes[i].finishTime);
    }
    return finish_times;
}





void FB2i::schedule(std::vector<Process>& processes){
    // vector of queue of processes
    std::vector<queue<Process *>> ready_queue;

}
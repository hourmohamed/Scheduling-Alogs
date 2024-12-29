#ifndef FB2I_H
#define FB2I_h

#include "Scheduler.h"


class FB2i :public Scheduler
{
public:
// int last_instant;
// FB2i(int last_instant){
//     this->last_instant = last_instant;
// }

    vector<vector<char>>timeline;

    void schedule(std::vector<Process>& processes, int last_instant) override;
    std::vector<int> calculate_finish_times(std::vector<Process>& processes) override;
    void fillInWaitTime(std::vector<Process> & processes){
    // bool is_empty_queues(queue<Process *> ready_queues[], int n);
    }    
    
};




#endif
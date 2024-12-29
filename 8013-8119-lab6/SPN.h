#ifndef SPN_H
#define SPN_H

#include "Scheduler.h"


class SPN : public Scheduler 
{

public:
    // SPN();
    // ~SPN();

    void schedule(std::vector<Process>& processes, int last_instant) override ;
    std::vector<int> calculate_finish_times(std::vector<Process>& processes) override ;
    
    

};






#endif








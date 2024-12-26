#ifndef SPN_H
#define SPN_H

#include "Scheduler.h"


class SPN : public Scheduler 
{

public:
    // SPN();
    // ~SPN();

    void schedule(std::vector<Process>& processes) override ;
    std::vector<int> calculate_finish_times(std::vector<Process>& processes) override ;
    
    

};






#endif








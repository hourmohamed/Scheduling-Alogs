#ifndef HRRN_H
#define HRRN_N

#include "Scheduler.h"


class HRRN : public Scheduler{
   public:
    // HRRN();
    // ~HRRN();

    void schedule(std::vector<Process>& processes) override ;
    std::vector<int> calculate_finish_times(std::vector<Process>& processes) override ;
    

};
#endif
#ifndef HRRN_H
#define HRRN_N

#include "Scheduler.h"


class HRRN : public Scheduler{
   public:
    // HRRN();
    // ~HRRN();

    void schedule(std::vector<Process>& processes, int last_instant) override ;
    std::vector<int> calculate_finish_times(std::vector<Process>& processes) override ;
    // int calculate_wait_time(Process p);

};
#endif
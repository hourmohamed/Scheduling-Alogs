#ifndef ROUNDROBIN_H
#define ROUNDROBIN_H

#include "Scheduler.h"
class RoundRobin : public Scheduler
{
    public :
    void sort_by_arrival(std::vector<Process>& processes);
    void schedule(std::vector<Process>& processes, int last_instant) override;
    std::vector<int> calculate_finish_times(std::vector<Process>& processes) override ;
};
#endif
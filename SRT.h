#ifndef SRT_H
#define SRT_H

#include "Scheduler.h"
class SRT : public Scheduler
{
    public :
    void sort_by_arrival(std::vector<Process>& processes);
    void schedule(std::vector<Process>& processes, int lastinstant) override;
    std::vector<int> calculate_finish_times(std::vector<Process>& processes) override ;
};
#endif
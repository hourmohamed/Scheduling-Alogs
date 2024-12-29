#ifndef FCFS_H
#define FCFS_H

#include "Scheduler.h"

class FCFS : public Scheduler {
public:
    void schedule(std::vector<Process>& processes, int last_instant) override;
    std::vector<int> calculate_finish_times(std::vector<Process>& processes) override;
    // void sort_by_arrival(std::vector<Process>& processes);
};

#endif // FCFS_H

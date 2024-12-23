#ifndef FCFS_H
#define FCFS_H

#include "Scheduler.h"

class FCFS : public Scheduler {
public:
    void schedule(std::vector<Process>& processes) override;
    int calculate_finish_time(Process p) override;
    void sort_by_arrival(std::vector<Process>& processes);

};

#endif // FCFS_H

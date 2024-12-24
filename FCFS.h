#ifndef FCFS_H
#define FCFS_H

#include "Scheduler.h"

class FCFS : public Scheduler {
public:

    void sort_by_arrival(std::vector<Process>& processes);
    void schedule(std::vector<Process>& processes) override;
    std::vector<int> calculate_finish_times(std::vector<Process>& processes) override ;
   

};

#endif // FCFS_H

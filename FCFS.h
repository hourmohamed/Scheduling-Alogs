#ifndef FCFS_H
#define FCFS_H

#include "Scheduler.h"

class FCFS : public Scheduler {
public:

    void sort_by_arrival(std::vector<Process>& processes);
    void schedule(std::vector<Process>& processes) override;
    int calculate_finish_time(Process p) override ;
   

};

#endif // FCFS_H

#ifndef FB2I_H
#define FB2I_h

#include "Scheduler.h"


class FB2i :public Scheduler
{
public:
    void schedule(std::vector<Process>& processes, int last_instant) override;
    std::vector<int> calculate_finish_times(std::vector<Process>& processes) override;
    
};




#endif
#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include<string>
#include "Process.h"



extern const std::string algos[];

class Scheduler {
public:
    const std::string TRACE = "trace";
    const std::string STATS = "stats";
    
    

    virtual void schedule(std::vector<Process>& processes) = 0;
    virtual int calculate_finish_time(Process p) = 0;

    virtual int calculate_turnaround(std::vector<Process>& processes);

    
    std::vector<double> calculate_normturn(const std::vector<Process>& processes);
    std::vector<int> calculate_turnaround_times(const std::vector<Process>& processes);

    virtual void printTrace(const std::vector<Process>& processes);
    int processes_count(std::vector<Process>& processes);
    void print_process(std::vector<Process>& processes);
    void print_arrival(std::vector<Process>& processes);
    void print_service(std::vector<Process>& processes);
    void printNormTurn(std::vector<Process>& processes);
    void print_turnaround(const std::vector<Process>& processes, const std::vector<int>& turnaround_times);
    void printFinishTime(std::vector<Process>& processes);
    void stats(int algo_index, std::vector<Process> processes);

    virtual ~Scheduler() = default;
};

#endif // SCHEDULER_H

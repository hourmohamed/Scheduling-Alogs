#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include <stdexcept>  // Include for error handling
#include "Process.h"

extern const std::string algos[];

class Scheduler {
public:
    virtual ~Scheduler() {}
    const std::string TRACE = "trace";
    const std::string STATS = "stats";
    int quantum=0;
    int time_line=0;
    virtual void schedule(std::vector<Process>& processes, int lastInstant) = 0;
    virtual std::vector<int> calculate_finish_times(std::vector<Process>& processes) = 0;  // Pure virtual

    std::vector<double> calculate_normturn(std::vector<Process>& processes);
    std::vector<int> calculate_turnaround(std::vector<Process>& processes);

    void sort_by_arrival(std::vector<Process>& processes);
    void sort_by_service(std::vector<Process>& processes);

    int processes_count(std::vector<Process>& processes);
    void printTrace(int algo_index,const std::vector<Process>& processes);
    void print_process(std::vector<Process>& processes);
    void print_arrival(std::vector<Process>& processes);
    void print_service(std::vector<Process>& processes);
    void printNormTurn(std::vector<Process>& processes);
    void print_turnaround(std::vector<Process>& processes, std::vector<int>& turnaround_times);
    void printFinishTime(std::vector<Process>& processes);
    void stats(int algo_index, std::vector<Process> processes);
};

#endif // SCHEDULER_H

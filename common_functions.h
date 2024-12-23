#ifndef COMMON_FUNCTIONS_H
#define COMMON_FUNCTIONS_H

#include <vector>
#include <string>




const std::string TRACE = "trace";
const std::string STATS = "stats";
const std::string algos[8] = {"FCFS", "RR", "SPN", "SRT", "HRRN", "FB-1", "FB-21", "AGING"};


struct Process {
    char name;
    int arrival_time;
    int service_time;
};

std::vector<Process> parse_processes(const std::string& processes_list);
void sort_by_arrival(std::vector<Process>& processes);
void sort_by_service(std::vector<Process>& processes);
void stats(int algo_index, std::vector<Process>& processes);
void trace();
void shortest_time_remaining();
int processes_count(std::vector<Process>& processes);

// void print_arrival(std::vector<Process>& processes);
// void print_process(std::vector<Process>& processes);
// void print_normturn(std::vector<Process>& processes);
// void print_turnaround(std::vector<Process>& processes);

#endif // PROCESS_H

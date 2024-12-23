#include<iostream>
#include<stdio.h>
#include <vector>
#include<string>
#include<sstream>
#include <iomanip>
#include<algorithm>
#include "common_functions.h"


// FCFS  0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 
// ------------------------------------------------
// A     |*|*|*| | | | | | | | | | | | | | | | | | 
// B     | | |.|*|*|*|*|*|*| | | | | | | | | | | | 
// C     | | | | |.|.|.|.|.|*|*|*|*| | | | | | | | 
// D     | | | | | | |.|.|.|.|.|.|.|*|*|*|*|*| | | 
// E     | | | | | | | | |.|.|.|.|.|.|.|.|.|.|*|*| 
// ------------------------------------------------




std::vector<Process> parse_processes(const std::string& processes_list) {
    std::vector<Process> processes;
    std::stringstream ss(processes_list);
    std::string process_desc;

    while (std::getline(ss, process_desc, ',')) {
        Process p;
        std::stringstream process_stream(process_desc);
        process_stream >> p.name;
        process_stream.ignore(1, ',');  
        process_stream >> p.arrival_time;
        process_stream.ignore(1, ',');  
        process_stream >> p.service_time;

        processes.push_back(p);
    }

    return processes;
}


void trace(){

}

int processes_count(std::vector<Process> processes){
    return processes.size();

}

// int get_finish_time(Process p){
//     return p.arrival_time+p.service_time;
// }


void print_process(std::vector<Process> processes){
    int num_processes = processes_count(processes);
    std::cout << "Process    ";
    for (int i = 0; i < num_processes; i++)
        std::cout << "|  " << processes[i].name << "  ";
    std::cout << "|\n";

}

void print_arrival(std::vector<Process> processes){
    int num_processes = processes_count(processes);
    std::cout << "Arrival    ";
    for (int i = 0; i < num_processes; i++)
        printf("|%3d  ",processes[i].arrival_time);
    std::cout<<"|\n";

}


void print_service(std::vector<Process> processes)
{
    int num_processes = processes_count(processes);
    std::cout << "Service    |";
    for (int i = 0; i < num_processes; i++)
        printf("%3d  |",processes[i].service_time);
    std::cout << " Mean|\n";
}



// void print_finish(std::vector<Process> processes) {
//     int num_processes = processes_count(processes);
    
//     int current_time = 0;  
//     std::cout << "Finish     ";

//     for (int i = 0; i < num_processes; i++) {
        
//         current_time = std::max(current_time, processes[i].arrival_time);
        
        
//         current_time += processes[i].service_time;
        
       
//         printf("|%3d  ", current_time);
//     }

//     std::cout << "|-----|\n";
// }
 


void print_turnaround(std::vector<Process> processes){

}

void print_normturn(std::vector<Process> processes){

}

void stats(int algo_index, std::vector<Process> processes){
    std::cout << algos[algo_index] << std::endl;
    
    print_process(processes);
    print_arrival(processes);
    print_finish(processes);
    print_turnaround(processes);
    print_normturn(processes);

}



void sort_by_arrival(std::vector<Process>& processes) {
    std::sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.arrival_time < b.arrival_time;
    });
}

void sort_by_service(std::vector<Process>& processes) {
    std::sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.service_time < b.service_time;
    });
}



void shortest_time_remaining(){

}




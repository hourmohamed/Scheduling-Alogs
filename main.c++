#include<iostream>
#include<stdio.h>


#include "common_functions.h"
#include "FCFS.cpp"


// # inputs:
// # 1- stat or trace
// # 2- algorithm to be tested (comma separating)
// # 3- last instant to be used in your simulation and to be shown on the timeline
// # 4- number of processes
// # 5- comma separated list for process name, arrival time, service time


void execute_algo(char algo, std::string operation, std::vector<Process> processes){
    switch(algo){
        case '1':
            if (operation == TRACE){
                trace();
            }
            else if(operation == STATS){
                stats(1, processes);
            }
            FCFS();
            break;
        case '2':
        if (operation == TRACE){
                trace();
            }
            else if(operation == STATS){
                stats(2, processes);
            }
            // round robin
            break;
        case '3':
        if (operation == TRACE){
                trace();
            }
            else if(operation == STATS){
                stats(3, processes);
            }
            //SPN
            break;
        case '4':
        if (operation == TRACE){
                trace();
            }
            else if(operation == STATS){
                stats(4, processes);
            }
            // srt
            break;
        case '5':
        if (operation == TRACE){
                trace();
            }
            else if(operation == STATS){
                stats(5, processes);
            }
            // HRRN
            break;
        case '6':
        if (operation == TRACE){
                trace();
            }
            else if(operation == STATS){
                stats(6, processes);
            }
            // FB-1
            break;
        case '7':
        if (operation == TRACE){
                trace();
            }
            else if(operation == STATS){
                stats(7, processes);
            }
            // FB-2i
            break;
        case '8':
        if (operation == TRACE){
                trace();
            }
            else if(operation == STATS){
                stats(8, processes);
            }
            // aging
            break;
        default:
            break;

    }
}



int main(int argc, char* argv[]){

    if (argc != 6) {
        std::cerr << "Incorrect inputs!" << std::endl;
        return 1; 
    }

    std::string state = argv[1];
    std::string algos_list = argv[2];
    int last_instant = std::stoi(argv[3]);
    int num_processes = std::stoi(argv[4]);
    std::string processes_list = argv[5];

    
    std::vector<Process> processes = parse_processes(processes_list);


    return 0;
}
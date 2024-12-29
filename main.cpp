#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include "Process.h"
#include "Scheduler.h"
#include "FCFS.h"
#include "RoundRobin.h"
#include "SPN.h"
#include "SRT.h"
#include "HRRN.h"
#include "FB2i.h"
#include "FB_1.h"
#include "Aging.h"

#include <iostream>
#include <vector>
#include <sstream>
#include <string>
using namespace std;

void parseInput(std::vector<Scheduler *> &schedulers, std::vector<Process> &processes, std::string &visualizationType, int &lastInstant, std::string &selected_algo)
{
    std::string line;
    std::vector<Scheduler *> localSchedulers;

    std::getline(std::cin, line);
    visualizationType = line;

    std::getline(std::cin, line);
    std::stringstream ss(line);
    std::string policy;
    int i = 0;
    while (std::getline(ss, policy, ','))
    {    
        std::string policyName;
        int policyType;
        int quantum = -1;

        std::stringstream policyStream(policy);
        if (policy.find("-") != std::string::npos)
        {
            std::getline(policyStream, policyName, '-');
            policyStream >> quantum;
        }
        else
        {
            policyName = policy;
        }

        policyType = std::stoi(policyName);
        
        switch (policyType)
        {
        case 1:
            localSchedulers.push_back(new FCFS());
            selected_algo = "FCFS";
            break;
        case 2:
            {
                RoundRobin* rr = new RoundRobin();
                if (quantum != -1) {
                    rr->quantum = quantum;
                }
                localSchedulers.push_back(rr);
                selected_algo = "RR";
            }
            break;
        case 3:
            localSchedulers.push_back(new SPN());
            selected_algo = "SPN";
            break;
        case 4:
            localSchedulers.push_back(new SRT());
            selected_algo = "SRT";
            break;
        case 5:
            localSchedulers.push_back(new HRRN());
            selected_algo = "HRRN";
            break;
        case 6:
            localSchedulers.push_back(new FB_1());
            selected_algo = "FB-1";
            break;
        case 7:
            localSchedulers.push_back(new FB2i());
            selected_algo = "FB-2i";
            break;
        case 8:
            {
                Aging* aging = new Aging();
                if (quantum != -1) {
                    aging->quantum = quantum;
                }
                localSchedulers.push_back(aging);
                selected_algo = "Aging";
            }
            break;
        default:
            std::cerr << "Error: Unknown policy " << policyType << std::endl;
            return;
        }
        i++;
    }

    schedulers = localSchedulers;

    std::getline(std::cin, line);
    lastInstant = std::stoi(line);

    std::getline(std::cin, line);
    int numProcesses = std::stoi(line);

    processes.clear();
    for (int i = 0; i < numProcesses; ++i)
    {
        std::getline(std::cin, line);
        std::stringstream processStream(line);
        char name;
        int arrivalTime, serviceTime;

        processStream >> name;
        processStream.ignore(1);
        processStream >> arrivalTime;
        processStream.ignore(1);
        processStream >> serviceTime;

        processes.push_back(Process(name, arrivalTime, serviceTime, lastInstant));
    }
}

int get_index(const std::string &algo_name)
{

    for (int i = 0; i < 8; ++i)
    {
        if (algo_name == algos[i])
        {
            return i;
        }
    }
    return -1;
}

int main()
{
    std::vector<Scheduler *> schedulers;
    std::vector<Process> processes;
    std::string visualizationType;
    int lastInstant;
    std::string selected_algo;

    parseInput(schedulers, processes, visualizationType, lastInstant, selected_algo);

    if (visualizationType == "trace")
    {
        for (auto &scheduler : schedulers)
        {
            // Create a fresh copy of processes for each scheduler
            std::vector<Process> processesCopy = processes;
            
            // Set timeline for the scheduler
            scheduler->time_line = lastInstant;
            
            // Run the scheduler
            scheduler->schedule(processesCopy, lastInstant);
            
            // Get the appropriate algorithm index for trace printing
            int algo_index;
            if (dynamic_cast<FCFS*>(scheduler)) algo_index = 0;
            else if (dynamic_cast<RoundRobin*>(scheduler)) algo_index = 1;
            else if (dynamic_cast<SPN*>(scheduler)) algo_index = 2;
            else if (dynamic_cast<SRT*>(scheduler)) algo_index = 3;
            else if (dynamic_cast<HRRN*>(scheduler)) algo_index = 4;
            else if (dynamic_cast<FB_1*>(scheduler)) algo_index = 5;
            else if (dynamic_cast<FB2i*>(scheduler)) algo_index = 6;
            else if (dynamic_cast<Aging*>(scheduler)) algo_index = 7;
            else algo_index = 0;

            // Print trace using the scheduler's trace method
            scheduler->printTrace(algo_index, processesCopy);
        }
    }
    else if (visualizationType == "stats")
    {
        for (auto &scheduler : schedulers)
        {
            // Create a fresh copy of processes for each scheduler
            std::vector<Process> processesCopy = processes;
            
            // Set timeline for the scheduler
            scheduler->time_line = lastInstant;
            
            // Run the scheduler
            scheduler->schedule(processesCopy, lastInstant);
            
            // Get the appropriate algorithm index for stats
            int algo_index;
            if (dynamic_cast<FCFS*>(scheduler)) algo_index = 0;
            else if (dynamic_cast<RoundRobin*>(scheduler)) algo_index = 1;
            else if (dynamic_cast<SPN*>(scheduler)) algo_index = 2;
            else if (dynamic_cast<SRT*>(scheduler)) algo_index = 3;
            else if (dynamic_cast<HRRN*>(scheduler)) algo_index = 4;
            else if (dynamic_cast<FB_1*>(scheduler)) algo_index = 5;
            else if (dynamic_cast<FB2i*>(scheduler)) algo_index = 6;
            else if (dynamic_cast<Aging*>(scheduler)) algo_index = 7;
            else algo_index = 0;
            
            // Print stats using the scheduler's stats method
            scheduler->stats(algo_index, processesCopy);
        }
    }

    // Cleanup
    for (auto scheduler : schedulers) {
        delete scheduler;
    }

    return 0;
}
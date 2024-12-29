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

using namespace std;

vector<int> parseInput(std::vector<Scheduler *> &schedulers, std::vector<Process> &processes, std::string &visualizationType, int &lastInstant, std::string &selected_algo)
{
    std::string line;
    std::vector<Scheduler *> localSchedulers;
    std::vector<int> policies;
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
        int quantum = -1; // Default value for quantum

        std::stringstream policyStream(policy);
        if (policy.find("-") != std::string::npos)
        {
            std::getline(policyStream, policyName, '-');
            policyStream >> quantum; // Extract the quantum value
        }
        else
        {
            policyName = policy;
        }

        policyType = std::stoi(policyName); // Convert to integer for the policy type
        policies.push_back(policyType);

        // Switch on policyType to add the correct scheduler
        switch (policyType)
        {
        case 1: // FCFS
            localSchedulers.push_back(new FCFS());
            selected_algo = "FCFS";
            break;
        case 2: // RoundRobin
            localSchedulers.push_back(new RoundRobin());
            if (quantum != -1)
                localSchedulers[i]->quantum = quantum;
            selected_algo = "RR";
            break;
        case 3: // SPN
            localSchedulers.push_back(new SPN());
            selected_algo = "SPN";
            break;
        case 4: // SRT
            localSchedulers.push_back(new SRT());
            selected_algo = "SRT";
            break;
        case 5: // HRRN
            localSchedulers.push_back(new HRRN());
            selected_algo = "HRRN";
            break;
        case 6: // FB-1
            localSchedulers.push_back(new FB_1());
            selected_algo = "FB-1";
            break;
        case 7: // FB-2i
            localSchedulers.push_back(new FB2i());
            selected_algo = "FB-2i";
            break;
        case 8: // Aging
            localSchedulers.push_back(new Aging());
            if (quantum != -1)
                localSchedulers[i]->quantum = quantum;
            selected_algo = "Aging";
            break;
        default:
            std::cerr << "Error: Unknown policy " << policyType << std::endl;
            break;
        }

        i++; // Move to the next scheduler
    }

    schedulers = localSchedulers;

    std::getline(std::cin, line);
    lastInstant = std::stoi(line);

    std::getline(std::cin, line);
    int numProcesses = std::stoi(line);
    schedulers[0]->time_line = lastInstant;

    processes.clear();
    for (int i = 0; i < numProcesses; ++i)
    {
        std::getline(std::cin, line);
        std::stringstream processStream(line);
        char name;
        int arrivalTime, serviceTime;

        processStream >> name;
        processStream.ignore(1); // Ignore the space
        processStream >> arrivalTime;
        processStream.ignore(1); // Ignore the space
        processStream >> serviceTime;

        processes.push_back(Process(name, arrivalTime, serviceTime, lastInstant));
    }

    return policies;
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
    vector<int> policies;

    // Parse input to initialize schedulers and processes
    policies = parseInput(schedulers, processes, visualizationType, lastInstant, selected_algo);

    // Create deep copies of processes for each scheduler
    vector<vector<Process>> copy_processes(schedulers.size());
    for (size_t i = 0; i < schedulers.size(); ++i)
    {
        // Clear the target vector to ensure it’s empty
        copy_processes[i].clear();

        // Perform a deep copy of the processes for this scheduler
        copy_processes[i] = processes; // This performs a deep copy of the vector
    }

    // Loop over schedulers and assign a unique algo_index for each one based on policies
    for (size_t i = 0; i < schedulers.size(); ++i)
    {
        int algo_index = policies[i-1];  // Corrected to use policies[i] instead of policies[i-1]

        // Check the visualization type and call the appropriate function
        if (visualizationType == "trace")
        {
            // Schedule the processes and print the trace for the scheduler
            schedulers[i]->schedule(copy_processes[i], lastInstant);
            //cerr<<copy_processes[i][0].finishTime<<copy_processes[i+1][0].finishTime;
            schedulers[i]->printTrace(algo_index, copy_processes[i]);
        }
        else if (visualizationType == "stats")
        {
            // Schedule the processes and print the stats for the scheduler
            schedulers[i]->schedule(copy_processes[i], lastInstant);
            schedulers[i]->stats(algo_index, copy_processes[i]);
        }
        else
        {
            std::cerr << "Error: Unknown visualization type " << visualizationType << std::endl;
        }

        // Cleanup: Delete the scheduler after use
        delete schedulers[i];
    }

    return 0;
}

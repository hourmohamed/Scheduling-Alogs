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

#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include "Scheduler.h"
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
            // std::cerr << "fcfs picked" << std::endl;

            selected_algo = "FCFS";
            break;
        case 2:
            if (quantum != -1)
            {

                // cout <<quantum;
                // Scheduler rr=new RoundRobin();
                localSchedulers.push_back(new RoundRobin());
                localSchedulers[0]->quantum = quantum;
                selected_algo = "RR";
            }
            break;

        case 3:
            // SPN
            selected_algo = "SPN";
            break;
        case 4:
            // SRT
            selected_algo = "SRT";
            break;
        case 5:
            // HRRN
            selected_algo = "HRRN";
            break;
        case 6:
            // FB-1
            selected_algo = "FB-1";
            break;
        case 7:
            // FB-2i
            selected_algo = "FB-2i";
            break;
        case 8:
            if (quantum != -1)
            {
                selected_algo = "AGING";
            }
            break;

        default:
            std::cerr << "Error: Unknown policy " << policyType << std::endl;
            return;
        }
    }

    schedulers = localSchedulers;

    std::getline(std::cin, line);
    lastInstant = std::stoi(line);
    std::cerr << "last instant: " << lastInstant << std::endl;

std::getline(std::cin, line);
int numProcesses = std::stoi(line);
schedulers[0]->time_line = lastInstant;

std::cerr << "Number of processes: " << numProcesses << std::endl;

processes.clear();
for (int i = 0; i < numProcesses; ++i)
{
    std::getline(std::cin, line);
    std::stringstream processStream(line);
    char name;
    int arrivalTime, serviceTime;

    processStream >> name;
    processStream.ignore(1);  // Ignore the space
    processStream >> arrivalTime;
    processStream.ignore(1);  // Ignore the space
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

    int algo_index = get_index(selected_algo);

    for (auto &scheduler : schedulers)
    {
        // cout <<scheduler->quantum;
        if (visualizationType == "trace")
        {
           
            

            scheduler->schedule(processes);
            scheduler->printTrace(algo_index, processes);
        }
        else if (visualizationType == "stats")
        {
            // cout <<processes[0].name;
            scheduler->schedule(processes);
            scheduler->stats(algo_index, processes);
        }
        delete scheduler;
    }

    return 0;
}

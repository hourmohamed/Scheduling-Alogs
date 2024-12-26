#include "Scheduler.h"
#include <stdexcept>
#include <algorithm>

using namespace std;

const std::string algos[8] = {"FCFS", "RR", "SPN", "SRT", "HRRN", "FB-1", "FB-2i", "AGING"};

std::vector<double> Scheduler::calculate_normturn(std::vector<Process> &processes)
{
    std::vector<double> normturns;

    // std::cerr << "in calc norm turn" << std::endl;

    std::vector<int> turnaround_times = calculate_turnaround(processes);
    // std::cerr << "after calc turnaround" << std::endl;

    for (size_t i = 0; i < processes.size(); ++i)
    {
        const auto &process = processes[i];

        if (process.serviceTime <= 0)
        {
            throw std::invalid_argument("Service time must be greater than 0");
        }

        int turnaround_time = turnaround_times[i];

        double normturn = static_cast<double>(turnaround_time) / process.serviceTime;
        normturns.push_back(normturn);
    }

    return normturns;
}

std::vector<int> Scheduler::calculate_turnaround(std::vector<Process> &processes)
{
    std::vector<int> turnaround_times;
    std::vector<int> finish_times;

    finish_times = calculate_finish_times(processes);

    // std::cerr << "in calc turn around" << std::endl;

    if (processes.empty())
    {
        std::cerr << "Error: No processes to calculate turnaround times." << std::endl;
        return turnaround_times;
    }
    for (int i = 0; i < processes.size(); i++)
    {
        // std::cerr << "bef calc finish timer" << std::endl;
        processes[i].finishTime = finish_times[i];
        // std::cerr << "after calc finish timer" << std::endl;
        // std::cerr << processes[i].finishTime << std::endl;

        if (processes[i].finishTime < processes[i].arrivalTime)
        {
            // std::cerr << "finish time cannot be earlier than arrival time for process." << " " << process.name << std::endl;
            continue;
        }

        int turnaround_time = processes[i].finishTime - processes[i].arrivalTime;
        turnaround_times.push_back(turnaround_time);
    }

    return turnaround_times;
}

int Scheduler::processes_count(std::vector<Process> &processes)
{
    return processes.size();
}

void Scheduler::print_process(std::vector<Process> &processes)
{
    int num_processes = processes_count(processes);
    std::cout << "Process    ";
    for (int i = 0; i < num_processes; i++)
    {
        std::cout << "|  " << processes[i].name << "  ";
    }
    std::cout << "|\n";
}

void Scheduler::print_arrival(std::vector<Process> &processes)
{
    int num_processes = processes_count(processes);
    std::cout << "Arrival    ";
    for (int i = 0; i < num_processes; i++)
    {
        printf("|%3d  ", processes[i].arrivalTime);
    }
    std::cout << "|\n";
}

void Scheduler::print_service(std::vector<Process> &processes)
{
    int num_processes = processes_count(processes);
    std::cout << "Service    |";
    for (int i = 0; i < num_processes; i++)
    {
        printf("%3d  |", processes[i].serviceTime);
    }
    std::cout << " Mean|\n";
}

void Scheduler::printNormTurn(std::vector<Process> &processes)
{
    // std::cerr << "in print norm turn" << std::endl;
    std::cout << "NormTurn   |";

    std::vector<double> normTurn;

    normTurn = calculate_normturn(processes);
    double sum = 0;

    for (int i = 0; i < normTurn.size(); i++)
    {
        sum += normTurn[i];
    }

    for (double normTurnValue : normTurn)
    {
        if (normTurnValue >= 10.0)
            printf("%2.2f|", normTurnValue);
        else
            printf(" %2.2f|", normTurnValue);
    }

    double averageNormTurn = sum / normTurn.size();
    if (averageNormTurn >= 10.0)
        printf("%2.2f|\n", averageNormTurn);
    else
        printf(" %2.2f|\n", averageNormTurn);
}

void Scheduler::print_turnaround(std::vector<Process> &processes, std::vector<int> &turnaround_times)
{
    double total_turnaround = 0.0;
    int num_processes = processes.size();

    std::cout << "Turnaround ";

    for (int i = 0; i < num_processes; ++i)
    {
        total_turnaround += turnaround_times[i];

        printf("|%3d  ", turnaround_times[i]);
    }

    double mean_turnaround = total_turnaround / num_processes;
    if (mean_turnaround <= 10)
        std::cout << "| " << std::fixed << std::setprecision(2) << mean_turnaround << "|\n";
    else
        std::cout << "|" << std::fixed << std::setprecision(2) << mean_turnaround << "|\n";
}

void Scheduler::printFinishTime(std::vector<Process> &processes)
{
    int num_processes = processes_count(processes);
    std::cout << "Finish     ";
    for (int i = 0; i < num_processes; i++)
    {
        printf("|%3d  ", processes[i].finishTime);
    }
    std::cout << "|-----|\n";
}

void Scheduler::stats(int algo_index, std::vector<Process> processes)
{

    std::cout << algos[algo_index];
    if (this->quantum != 0)
        cout << "-" << this->quantum;
    cout << endl;
    print_process(processes);
    print_arrival(processes);
    print_service(processes);
    printFinishTime(processes);

    std::vector<int> turnaround_times = calculate_turnaround(processes);
    print_turnaround(processes, turnaround_times);

    printNormTurn(processes);
}

void Scheduler::printTrace(int algo_index,const std::vector<Process> &processes)
{
    std::cout << algos[algo_index];
    if (this->quantum != 0)
        cout << "-" << this->quantum;
    int i=this->time_line/10;
    int j=this->time_line%10;

    while (i--)
    {
        for (int k=0;k<10;k++)
            cout <<" "<<k;
        
    }
    for (int k=0;k<j;k++)
        cout<<" "<<k ;
    
    cout << " 0"<<endl;
    for (int i = 0; i < processes.size(); i++)
    {
        cout <<processes[i].name <<"    ";
        for (int j=0;j<this->time_line;j++)
            {
                cout <<"|";
                if (processes[i].state.at(j)==1)
                    cout <<"*";
                else if (processes[i].state.at(j)==0)
                    cout <<".";
                else 
                    cout <<" ";
            }
        cout <<"|"<<endl;
    }
}

void Scheduler::sort_by_arrival(std::vector<Process> &processes)
{
    std::sort(processes.begin(), processes.end(), [](const Process &a, const Process &b)
              { return a.arrivalTime < b.arrivalTime; });
}

void Scheduler::sort_by_service(std::vector<Process> &processes)
{
    std::sort(processes.begin(), processes.end(), [](const Process &a, const Process &b)
              { return a.serviceTime < b.serviceTime; });
}

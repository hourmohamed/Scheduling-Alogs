#include "Scheduler.h"
#include <stdexcept>  // Include for invalid_argument

// Default implementation for calculate_turnaround (can be overridden)


const std::string algos[8] = {"FCFS", "RR", "SPN", "SRT", "HRRN", "FB-1", "FB-2i", "AGING"};

int Scheduler::calculate_turnaround(std::vector<Process>& processes) {
    int totalTurnaround = 0;
    for (const auto& process : processes) {
        totalTurnaround += process.finishTime - process.arrivalTime;
    }
    return totalTurnaround;
}

// Definition of calculate_normturn method (note no 'Scheduler::' inside header)
std::vector<double> Scheduler::calculate_normturn(const std::vector<Process>& processes) {
    std::vector<double> normturns;

    for (const auto& process : processes) {
        int turnaround_time = process.finishTime - process.arrivalTime;

        if (process.serviceTime <= 0) {
            throw std::invalid_argument("Service time must be greater than 0");
        }

        double normturn = static_cast<double>(turnaround_time) / process.serviceTime;
        normturns.push_back(normturn);
    }

    return normturns;
}

std::vector<int> Scheduler::calculate_turnaround_times(const std::vector<Process>& processes) {
    std::vector<int> turnaround_times;
    for (const auto& process : processes) {
        int turnaround_time = process.finishTime - process.arrivalTime;
        turnaround_times.push_back(turnaround_time);
    }
    return turnaround_times;
}

void Scheduler::printTrace(const std::vector<Process>& processes) {
    std::cout << "Tracing processes...\n";
    for (const auto& process : processes) {
        std::cout << "Process " << process.name << ": "
                  << "Arrival Time=" << process.arrivalTime
                  << ", Finish Time=" << process.finishTime << "\n";
    }
}

int Scheduler::processes_count(std::vector<Process>& processes) {
    return processes.size();
}

void Scheduler::print_process(std::vector<Process>& processes) {
    int num_processes = processes_count(processes);
    std::cout << "Process    ";
    for (int i = 0; i < num_processes; i++) {
        std::cout << "|  " << processes[i].name << "  ";
    }
    std::cout << "|\n";
}

void Scheduler::print_arrival(std::vector<Process>& processes) {
    int num_processes = processes_count(processes);
    std::cout << "Arrival    ";
    for (int i = 0; i < num_processes; i++) {
        printf("|%3d  ", processes[i].arrivalTime);
    }
    std::cout << "|\n";
}

void Scheduler::print_service(std::vector<Process>& processes) {
    int num_processes = processes_count(processes);
    std::cout << "Service    |";
    for (int i = 0; i < num_processes; i++) {
        printf("%3d  |", processes[i].serviceTime);
    }
    std::cout << " Mean|\n";
}

void Scheduler::printNormTurn(std::vector<Process>& processes) {
    std::cout << "NormTurn   |";

    std::vector<double> normTurn;
    double sum = 0;

    for (const auto& process : processes) {
        int turnaroundTime = process.finishTime - process.arrivalTime;
        double normTurnValue = static_cast<double>(turnaroundTime) / process.serviceTime;
        normTurn.push_back(normTurnValue);
        sum += normTurnValue;
    }

    for (double normTurnValue : normTurn) {
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

void Scheduler::print_turnaround(const std::vector<Process>& processes, const std::vector<int>& turnaround_times) {
    double total_turnaround = 0.0;
    int num_processes = processes.size();

    std::cout << "Turnaround ";

    for (int i = 0; i < num_processes; ++i) {
        total_turnaround += turnaround_times[i];
        printf("|%3d  ", turnaround_times[i]);
    }

    double mean_turnaround = total_turnaround / num_processes;
    std::cout << "| " << std::fixed << std::setprecision(2) << mean_turnaround << "|\n";
}

void Scheduler::printFinishTime(std::vector<Process>& processes) {
    int num_processes = processes_count(processes);
    std::cout << "Finish     ";
    for (int i = 0; i < num_processes; i++) {
        printf("|%3d  ", processes[i].finishTime);
    }
    std::cout << "|-----|\n";
}

void Scheduler::stats(int algo_index, std::vector<Process> processes) {


    std::cout << algos[algo_index] << std::endl;

    print_process(processes);
    print_arrival(processes);
    print_service(processes);
    printFinishTime(processes);
    
    

    std::vector<int> turnaround_times = calculate_turnaround_times(processes);
    print_turnaround(processes, turnaround_times);

    printNormTurn(processes);

}



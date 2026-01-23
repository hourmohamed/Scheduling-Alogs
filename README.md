Scheduling-Alogs

A collection of CPU Scheduling Algorithm implementations in C++ for educational use, showcasing core process scheduling techniques used in operating systems.

📌 Overview

This repository implements classic CPU scheduling algorithms in C++, demonstrating how different strategies decide the order and timing of process execution. Scheduling is a key concept in operating systems that aims to efficiently manage CPU time among competing tasks.

🚀 Algorithms Included

Each algorithm is implemented as a separate module with supporting header (.h) and source (.cpp) files:

FCFS (First-Come, First-Served) – Simple non-preemptive algorithm.

Round Robin – Fair time-slice scheduling using a fixed quantum.

SPN (Shortest Process Next) – Chooses the shortest job next (non-preemptive).

HRRN (Highest Response Ratio Next) – Balances wait time and service time.

SRT (Shortest Remaining Time) – Preemptive variant of shortest job first.

Additionally, utility files such as Process.cpp/h and a main driver (main.cpp) orchestrate reading input and running selected algorithms.

📦 Repository Structure
Scheduling-Alogs/
├── .vscode/
├── testcases/
├── FCFS.cpp
├── FCFS.h
├── RoundRobin.cpp
├── RoundRobin.h
├── SPN.cpp
├── SPN.h
├── HRRN.cpp
├── HRRN.h
├── SRT.cpp
├── SRT.h
├── Process.cpp
├── Process.h
├── Scheduler.cpp
├── Scheduler.h
├── main.cpp
├── makefile
└── testcases.zip
``` :contentReference[oaicite:10]{index=10}

## 📥 Build & Run

To compile and run the project:

1. Clone the repo:  
   ```bash
   git clone https://github.com/hourmohamed/Scheduling-Alogs.git
   cd Scheduling-Alogs


Build using the provided makefile:

make


Run the executable:

./Scheduler


Performance analysis metrics.

A GUI or visualization tool.

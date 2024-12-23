# inputs:
# 1- stat or trace
# 2- algorithm to be tested (comma separating)
# 3- last instant to be used in your simulation and to be shown on the timeline
# 4- number of processes
# 5- comma separated list for process name, arrival time, service time

.PHONY: inputs

inputs:
@echo "stat or trace: "; \
read state; \
echo "algorithms to be tested: "; \
read algorithms; \
echo "last instant: "; \
read last_instant; \
echo "number of processes: "; \
read num_processed; \
echo "enter process name, arrival time, service time: "; \
read processed_list; \
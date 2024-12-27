#include "HRRN.h"
#include <queue>



void HRRN::schedule(std::vector<Process>& processes){

    sort_by_arrival(processes);

}

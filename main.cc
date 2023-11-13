#include "scheduler/main_scheduler.h"
#include "scheduler/base_unit/linked_list.h"
#include "scheduler/scheduling/RM_scheduling.h"
#include "scheduler/scheduling/EDF_scheduling.h"
#include "scheduler/scheduling/LST_scheduling.h"
#include <iostream>
#include <algorithm>

using namespace std;

int main(){

    string task = "task_data/test4.txt";

    scheduler<RM_scheduling> rm(task); 
    rm.start_scheduling();
    scheduler<EDF_scheduling> edf(task); 
    edf.start_scheduling();
    scheduler<LST_scheduling> lst(task); 
    lst.start_scheduling();
    return 0;
}

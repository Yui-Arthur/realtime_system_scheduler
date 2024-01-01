#include "scheduler/main_scheduler.h"
#include "scheduler/scheduler_with_aperiodic.h"
#include "scheduler/base_unit/linked_list.h"
#include "scheduler/scheduling/RM_scheduling.h"
#include "scheduler/scheduling/EDF_scheduling.h"
#include "scheduler/scheduling/LST_scheduling.h"

#include "scheduler/aperiodic_server/aperiodic_server.h"
#include "scheduler/aperiodic_server/CU_server.h"
#include "scheduler/aperiodic_server/TB_server.h"
#include <iostream> 
#include <algorithm>

using namespace std; 
int main(){

    string periodic_task = "periodic_task_data/test3_ver2_0.9.txt";
    string aperiodic_task = "aperiodic_task_data/complex_task.txt";

    // string periodic_task = "periodic_task_data/test1_ver2.txt";
    // string aperiodic_task = "aperiodic_task_data/simple_task.txt";

    
    // scheduler_with_aperiodic<EDF_scheduling,CU_server> edf_p(periodic_task, aperiodic_task, 0.2);
    scheduler_with_aperiodic<EDF_scheduling,TB_server> edf_p(periodic_task, aperiodic_task, 0.2);
    edf_p.start_scheduling();
    // scheduler<RM_scheduling> rm(task); 
    // rm.start_scheduling();
    // scheduler<EDF_scheduling> edf(periodic_task); 
    // edf.start_scheduling();
    // scheduler<LST_scheduling> lst(task); 
    // lst.start_scheduling();
    return 0;
}

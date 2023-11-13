#include "EDF_scheduling.h"


void EDF_scheduling::push_job(job j){
    int idx=0;
    for(auto i=jobs.begin(); i!=jobs.end(); i=i->next_node, idx+=1){
        if(j.absolute_deadline < i->t.absolute_deadline)
            break;
        else if(j.absolute_deadline == i->t.absolute_deadline && j.TID < i->t.TID)
            break;
    }

    jobs.insert_idx(idx,j);
}

bool EDF_scheduling::schedulability_test(linked_list<periodic_task>& tasks){
    float utilizations = 0;
    for(auto i = tasks.begin(); i != tasks.end(); i=i->next_node){
        periodic_task t = i->t;
        utilizations += t.execution_time / float(std::min(t.relative_deadline , t.period));
    }

    std::cout<< utilizations << std::endl;
    return utilizations <= 1;
}
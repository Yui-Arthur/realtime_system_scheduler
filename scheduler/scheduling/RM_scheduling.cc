#include "RM_scheduling.h"
#include <cmath>

RM_scheduling::RM_scheduling() : base_scheduling() {;};
RM_scheduling::RM_scheduling(linked_list<periodic_task> tasks) : base_scheduling(tasks){
    // insertion sort
    linked_list<periodic_task> sorted_tasks;
    RM_ready_queue = new linked_list<job>[tasks.size()];
    task_number = tasks.size();
    task_priority = new int[tasks.size()];
    for(auto i=tasks.begin(); i!=tasks.end(); i=i->next_node){

        int idx=0;
        for(auto j=sorted_tasks.begin(); j!=sorted_tasks.end(); j=j->next_node,idx+=1){
            if(i->t.period < j->t.period)
                break;
        };

        sorted_tasks.insert_idx(idx , i->t);
    }
    int idx=0;
    for(auto i = sorted_tasks.begin(); i!=sorted_tasks.end(); i=i->next_node, idx+=1){
        task_priority[i->t.TID] = idx;
    }

};

void RM_scheduling::push_job(job j) {
    RM_ready_queue[task_priority[j.TID]].push_back(j);
    return;
};

job* RM_scheduling::get_job(int clock){

    remove_done_job();

    for(int i=0; i<task_number; i++){
        if(RM_ready_queue[i].size() !=0)
            return &RM_ready_queue[i][0];
    }

    return &idle_job;

}

void RM_scheduling::remove_done_job(){
   for(int i=0; i<task_number; i++){
        int idx=0;
        for(auto j=RM_ready_queue[i].begin(); j!=RM_ready_queue[i].end() ; j=j->next_node, idx+=1)
            if(j->t.remain_execution_time == 0)
                RM_ready_queue[i].del_idx(idx);
    } 
}

int RM_scheduling::check_miss_deadline(int clock){
    int idx = 0;
    int miss_cnt = 0;
    
    for(int i=0; i<task_number; i++){
        linked_list<int> miss_jobs;
        for(auto j=RM_ready_queue[i].begin(); j!=RM_ready_queue[i].end() ; j=j->next_node, idx+=1){
            if(j->t.absolute_deadline - clock  < j->t.remain_execution_time){
                // std::cout<<clock<<" "<<j->t.absolute_deadline<<" "<<j->t.remain_execution_time<<"\n";
                std::cout<<"Clock "<<clock<<" T"<<j->t.TID << " will miss deadline on Clock "<<j->t.absolute_deadline<<"\n";
                miss_jobs.push_back(idx);
                miss_cnt += 1;
            }

            idx+=1;
        }
        idx = 0;
        for(auto j = miss_jobs.begin(); j != miss_jobs.end(); j=j->next_node){
            RM_ready_queue[i].del_idx(j->t - idx);
            idx += 1;
        }
    }

    return miss_cnt;
}

bool RM_scheduling::schedulability_test(linked_list<periodic_task>& tasks){
    float utilizations = 0;
    for(auto i = tasks.begin(); i != tasks.end(); i=i->next_node){
        periodic_task t = i->t;
        utilizations += t.execution_time / float(std::min(t.relative_deadline , t.period));
    }

    float RM_utilizations = tasks.size() * (std::pow(2,(1/float(tasks.size())))-1);
    std::cout<< utilizations <<" " << RM_utilizations << std::endl;
    return utilizations <= RM_utilizations;
}
#include "CU_server.h"

void CU_server::push_job(job j){
    replenishment_1(j);
    aperiodic_server::push_job(j);
}

job* CU_server::get_job(int t){
    if(deadline == t){
        replenishment_2(t);
    }

    remove_done_job(t);

    // std::cout<<"G "<< deadline <<" " <<budget<<"\n";

    if(jobs.size() == 0 || budget == 0)
        return &idle_job;
    else{
        jobs[0].absolute_deadline = deadline;        
        return &jobs[0];
    }
}

void CU_server::replenishment_1(job j){
    if(j.release_time >= deadline && jobs.size() == 0){
        deadline = j.release_time + j.remain_execution_time / server_size;
        budget = j.remain_execution_time;
    }
}

void CU_server::replenishment_2(int t){
    if(jobs.size() != 0){
        deadline = deadline + jobs[0].remain_execution_time / server_size;
        budget = jobs[0].remain_execution_time;
    }
}
#include "TB_server.h"

void TB_server::push_job(job j){
    replenishment_1(j);
    aperiodic_server::push_job(j);
}

job* TB_server::get_job(int t){

    remove_done_job(t);

    if(jobs.size() == 0 || budget == 0)
        return &idle_job;
    else{
        jobs[0].absolute_deadline = deadline;        
        return &jobs[0];
    }
}

void TB_server::remove_done_job(int t){
    int idx = 0;
    if(jobs.size()!=0 && jobs[0].remain_execution_time == 0){
        std::cout<<"\tresponse time " << t - jobs[0].release_time << "(" << t <<" - "<< jobs[0].release_time <<")\n";
        success_job +=1;
        excuse_time += t - jobs[0].release_time;
        std::cout<<"\ttotal response time " << excuse_time<<"\n";
        jobs.del_idx(0);

        replenishment_2(t);
    }
}

void TB_server::replenishment_1(job j){
    if(jobs.size() == 0){
        deadline = std::max(deadline, j.release_time) + j.remain_execution_time / server_size;
        budget = j.remain_execution_time;
    }
}

void TB_server::replenishment_2(int t){
    if(jobs.size() != 0){
        deadline = deadline + jobs[0].remain_execution_time / server_size;
        budget = jobs[0].remain_execution_time;
    }
}

#ifndef __APERIODIC_SERVER_H_
#define __APERIODIC_SERVER_H_


#include "../base_unit/task.h"
#include "../base_unit/linked_list.h"


class aperiodic_server{
    public:
        aperiodic_server(){;};
        aperiodic_server(float server_size): server_size(server_size) {idle_job.TID = -1, idle_job.absolute_deadline = 1e9;};
        
        void push_job(job j) {
            jobs.push_back(j);
        };
        job* get_job(int t){
            
            remove_done_job(t);

            if(jobs.size() == 0 || budget == 0)
                return &idle_job;
            else{
                jobs[0].absolute_deadline = deadline;               
                return &jobs[0];
            }
        };
        float get_total_response_time() {
            std::cout<<"T " << excuse_time <<" "<<success_job<<"\n";
            return excuse_time / float(success_job);
        }
        void consume_budget(){
            budget -= 1;
        }
        void print_budget_deadline(){
            std::cout<<"\tbudget " << budget << " deadline " << deadline <<"\n";
        }


    protected:
        linked_list<job> jobs;
        job idle_job;
        int deadline = 0;
        int budget = 0;
        float server_size;
        int success_job = 0;
        int excuse_time = 0;

        

        void remove_done_job(int t){
            int idx = 0;
            if(jobs.size()!=0 && jobs[0].remain_execution_time == 0){
                std::cout<<"\tresponse time " << t - jobs[0].release_time << "(" << t <<" - "<< jobs[0].release_time <<")\n";
                success_job +=1;
                excuse_time += t - jobs[0].release_time;
                std::cout<<"\ttotal response time " << excuse_time<<"\n";
                jobs.del_idx(0);
            }
        };
};

#endif
#ifndef _BASE_SCGEDULING_
#define _BASE_SCGEDULING_

#include "../base_unit/task.h"
#include "../base_unit/linked_list.h"
class base_scheduling{
    public:
        base_scheduling(){idle_job.TID = -1;};
        base_scheduling(linked_list<periodic_task>& tasks){idle_job.TID = -1, idle_job.absolute_deadline = 1e9;};
        void push_job(job j) {jobs.push_back(j);};
        job* get_job(int clock) {
            remove_done_job();

            if(jobs.size() == 0)
                return &idle_job;
            else
                return &jobs[0];
        };
        bool schedulability_test(linked_list<periodic_task>& tasks){
            float utilizations = 0;
            for(auto i = tasks.begin(); i != tasks.end(); i=i->next_node){
                periodic_task t = i->t;
                utilizations += t.execution_time / float(std::min(t.relative_deadline , t.period));
            }

            std::cout<< utilizations << std::endl;
            return utilizations <= 1;

        };

        int check_miss_deadline(int clock){
            int idx = 0;
            int miss_cnt = 0;
            linked_list<int> miss_jobs;
            for(auto i = jobs.begin(); i != jobs.end(); i=i->next_node){
                if(i->t.absolute_deadline - clock  < i->t.remain_execution_time){
                    std::cout<<"Clock "<<clock<<" T"<<i->t.TID << " will miss deadline on Clock "<<i->t.absolute_deadline<<"\n";
                    miss_jobs.push_back(idx);
                    miss_cnt += 1;
                }

                idx+=1;
            }

            idx = 0;
            for(auto i = miss_jobs.begin(); i != miss_jobs.end(); i=i->next_node){
                jobs.del_idx(i->t - idx);
                idx += 1;
            }

            return miss_cnt;

        }
        bool strict = false;
        std::string scheduling_method = "base";
    protected:
        linked_list<job> jobs;
        job idle_job = job();
        void remove_done_job(){
            int idx = 0;
            for(auto i = jobs.begin(); i != jobs.end(); i=i->next_node){
                if(i->t.remain_execution_time == 0){
                    jobs.del_idx(idx);
                    return;
                }

                idx+=1;
            }

        };

};


#endif
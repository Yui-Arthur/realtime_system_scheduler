#ifndef __RM_SCHEDULING_H_
#define __RM_SCHEDULING_H_

#include "base_scheduling.h"

class RM_scheduling : public base_scheduling{
    public:
        RM_scheduling();
        RM_scheduling(linked_list<periodic_task>);
        void push_job(job);
        job* get_job(int clock);
        int check_miss_deadline(int clock);
        bool schedulability_test(linked_list<periodic_task>&);
        std::string scheduling_method = "Rate_Monotonic";
        
    private:
        int* task_priority;
        int task_number;
        linked_list<job>* RM_ready_queue;
        void remove_done_job();
};

#include "RM_scheduling.cc"



#endif
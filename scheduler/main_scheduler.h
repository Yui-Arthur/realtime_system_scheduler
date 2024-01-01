#ifndef _MAIN_SCHEDULER_
#define _MAIN_SCHEDULER_

#include <iostream>
#include "base_unit/linked_list.h"
#include "base_unit/task.h"
#include "scheduling/base_scheduling.h"

template <class scheduling>
class scheduler {
    public:
        scheduler(){;};
        scheduler(std::string);
        void start_scheduling();
        void visualize_scheduling(linked_list<job>[] , linked_list<int>& , int);
        void save_scheduling(linked_list<int>& , int, std::string );
    protected:
        linked_list<periodic_task> all_periodic_tasks;    
        scheduling scheduling_method;
        void read_periodic_task(std::string);
        linked_list<job>* setting_periodic_task(int);
    private:
        int gcd(int a, int b);
        int calculate_task_LCM();
};

#include "main_scheduler.cc"
#endif
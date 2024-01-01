#ifndef _SCHEDULER_APERIODIC_
#define _SCHEDULER_APERIODIC_

#include <iostream>
#include "base_unit/linked_list.h"
#include "base_unit/task.h"
#include "scheduling/base_scheduling.h"
#include "aperiodic_server/aperiodic_server.h"

template <class scheduling, class aperiodic_server>
class scheduler_with_aperiodic : public scheduler<scheduling>{
    public:
        scheduler_with_aperiodic(std::string, std::string, float);
        void start_scheduling();
        linked_list<job>* setting_aperiodic_task(int end_clock);
        void visualize_scheduling(linked_list<job> [], linked_list<job> [], linked_list<std::pair<char,int> >& , int );
        // void visualize_scheduling(linked_list<job>[] , linked_list<int>& , int);
        // void save_scheduling(linked_list<int>& , int, std::string );
    private:
        linked_list<aperiodic_task> all_aperiodic_tasks;   
        float aperiodic_server_size;
        void read_task(std::string, char);
        
};

#include "scheduler_with_aperiodic.cc"
#endif
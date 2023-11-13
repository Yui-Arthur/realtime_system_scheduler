#ifndef __EDF_SCHEDULING_H_
#define __EDF_SCHEDULING_H_

#include "base_scheduling.h"

class EDF_scheduling : public base_scheduling{
    public:
        EDF_scheduling() : base_scheduling(){;};
        EDF_scheduling(linked_list<periodic_task> t): base_scheduling(t) {;};
        void push_job(job);
        bool schedulability_test(linked_list<periodic_task>&);
        std::string scheduling_method = "Earliest_Deadline_First";

};

#include "EDF_scheduling.cc"



#endif
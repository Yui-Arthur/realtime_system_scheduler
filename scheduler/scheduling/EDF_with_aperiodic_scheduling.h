#ifndef __EDF_APERIODIC_SCHEDULING_H_
#define __EDF_APERIODIC_SCHEDULING_H_

#include "base_scheduling.h"
#include "EDF_scheduling.h"



class EDF_with_aperiodic_scheduling : public EDF_scheduling{
    public:
        EDF_with_aperiodic_scheduling() : EDF_scheduling(){;};
        EDF_with_aperiodic_scheduling(linked_list<periodic_task> t): EDF_scheduling(t) {;};
        void push_job(job);
        bool schedulability_test(linked_list<periodic_task>&);
        std::string scheduling_method = "Earliest_Deadline_First_APERIODIC";

};

#include "EDF_with_aperiodic_scheduling.cc"



#endif
#ifndef __LST_SCHEDULING_H_
#define __LST_SCHEDULING_H_

#include "base_scheduling.h"

class LST_scheduling : public base_scheduling{
    public:
        LST_scheduling() : base_scheduling(){;};
        LST_scheduling(linked_list<periodic_task> t): base_scheduling(t) {;};
        // void push_job(job);
        job* get_job(int clock);
        bool strict = true;
        std::string scheduling_method = "Least_Slack_Time";
};

#include "LST_scheduling.cc"



#endif
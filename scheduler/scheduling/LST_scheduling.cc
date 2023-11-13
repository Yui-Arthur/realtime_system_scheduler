#include "LST_scheduling.h"


job* LST_scheduling::get_job(int clock){
    remove_done_job();
    int min_slack_time = 1e9 , min_idx=0 , min_TID = 0;

    int idx=0;
    for(auto i=jobs.begin(); i!=jobs.end(); i=i->next_node,idx++){
        int slack = i->t.absolute_deadline - clock - i->t.remain_execution_time;
        if(slack < min_slack_time)
            min_slack_time = slack, min_idx=idx, min_TID = i->t.TID;       
        else if(slack == min_slack_time && i->t.TID < min_TID)     
            min_slack_time = slack, min_idx=idx, min_TID = i->t.TID;       
    }

    if(jobs.size() == 0)
        return &idle_job;
    else
        return &jobs[min_idx];

}
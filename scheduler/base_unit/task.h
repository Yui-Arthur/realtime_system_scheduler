#ifndef _TASK_H_
#define _TASK_H_

#include <iomanip>
struct periodic_task
{
    int phase_time;
    int period;
    int relative_deadline;
    int execution_time;
    int TID;
    periodic_task() : phase_time(0), period(0), relative_deadline(0) , execution_time(0) , TID(0){}; 
    periodic_task(int *task_info) : phase_time(task_info[0]), period(task_info[1]), relative_deadline(task_info[2]) , execution_time(task_info[3]), TID(task_info[4]) {}; 
    friend std::ostream& operator<<(std::ostream& os, const periodic_task &task_info){
        os <<"T" <<task_info.TID << ": \n"
           <<std::left << std::setw(5) <<"  PT"<<"("<< task_info.phase_time <<")\n"
           <<std::left <<std::setw(5) <<"  P"<<"("<< task_info.period <<")\n"
           <<std::left <<std::setw(5) <<"  RD"<<"("<< task_info.relative_deadline << ")\n" 
           <<std::left <<std::setw(5) <<"  EXT"<<"("<< task_info.execution_time <<")\n\n";
        return os; 
    };
};

struct aperiodic_task
{
    int phase_time;
    int execution_time;
    int TID;
    aperiodic_task() : phase_time(0), execution_time(0) , TID(0){;}; 
    aperiodic_task(int *task_info) : phase_time(task_info[0]), execution_time(task_info[1]), TID(task_info[2]) {}; 
    friend std::ostream& operator<<(std::ostream& os, const aperiodic_task &task_info){
        os <<"AT" <<task_info.TID << ": \n"
           <<std::left << std::setw(5) <<"  PT"<<"("<< task_info.phase_time <<")\n"
           <<std::left <<std::setw(5) <<"  EXT"<<"("<< task_info.execution_time <<")\n\n";
        return os; 
    };
};

struct job
{
    int release_time;
    int absolute_deadline;
    int remain_execution_time;
    int TID;
    job() : release_time(0), absolute_deadline(0), remain_execution_time(0), TID(0) {}; 
    job(int *job_info) : release_time(job_info[0]), absolute_deadline(job_info[1]), remain_execution_time(job_info[2]), TID(job_info[3]){}; 
    friend std::ostream& operator<<(std::ostream& os, const job &job_info){
        os << job_info.TID << ":\n"
            <<"  "<< job_info.release_time <<", "
            <<"  "<< job_info.absolute_deadline <<", "
            <<"  "<< job_info.remain_execution_time << "\n";
        return os; 
    };
};

#endif
#include "main_scheduler.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>

template<class T> scheduler<T>::scheduler(std::string periodic_task_file){
    read_periodic_task(periodic_task_file);
};

template<class T> void scheduler<T>::read_periodic_task(std::string task_file){
    std::ifstream tasks_data(task_file); 
    std::string line_task , task_fragment;
    std::stringstream ss;
    while (std::getline(tasks_data, line_task)) {
        ss << line_task << ",";        
    }

    int cnt = 0;
    int task_info[5];
    while(std::getline(ss , task_fragment , ',')){
        task_info[cnt%4] = stoi(task_fragment);
        if(cnt%4 == 3)
            task_info[4] = (cnt/4) , all_periodic_tasks.push_back(periodic_task(task_info));
        cnt += 1;
    }
    
    tasks_data.close();

    // std::cout << all_periodic_tasks;
}

template<class T> void scheduler<T>::start_scheduling(){
    T scheduling(all_periodic_tasks);
    if(!scheduling.schedulability_test(all_periodic_tasks)){
        std::cout<<"Schedulability Test Fail\n\n";
    }

    std::cout<<scheduling.scheduling_method<<"\n\n";
    int end_clock = calculate_task_LCM();
    linked_list<job>* periodic_task_schedule = setting_periodic_task(end_clock);
    linked_list<int> scheduled_results;
    int miss_deadline_cnt = 0;

    // start with a empty job
    job* current_job = new job();
    for(int clock = 0; clock < end_clock; clock++){
        
        int current_miss = scheduling.check_miss_deadline(clock);
        miss_deadline_cnt += current_miss;

        // have job release in this clock
        for(auto i=periodic_task_schedule[clock].begin(); i != periodic_task_schedule[clock].end(); i = i->next_node){
            scheduling.push_job(i->t);
        }
        /* when
         *   job is over 
         *   new job release
         *   current clock has miss deadline job
         *   strict check the job
         * => re-pick the highest priority job
         */ 
        if(current_job->remain_execution_time == 0 || periodic_task_schedule[clock].size() != 0 || current_miss != 0 || scheduling.strict)
            current_job = scheduling.get_job(clock);
        
        current_job->remain_execution_time -= 1;

        scheduled_results.push_back(current_job->TID);
        // std::cout<< "Clock" << clock+1 << " " << current_job->TID << "\n";
        
    }

    visualize_scheduling(periodic_task_schedule , scheduled_results , end_clock);
    save_scheduling(scheduled_results , end_clock ,scheduling.scheduling_method);
}


template<class T> int scheduler<T>::calculate_task_LCM(){
    int lcm = 1;
    int max_phase_time = -1;
    for(auto i=all_periodic_tasks.begin(); i!=all_periodic_tasks.end(); i=i->next_node){
        periodic_task t = i->t;
        lcm = lcm * t.period / gcd(lcm , t.period);
        max_phase_time = std::max(max_phase_time , t.phase_time);
    }

    return lcm + max_phase_time;
}

template<class T> int scheduler<T>::gcd(int a , int b){
    if(a < b) std::swap(a,b);
    if(a%b == 0) return b;
    else return gcd(b , a%b);
}

template<class T> linked_list<job>* scheduler<T>::setting_periodic_task(int end_clock){
    linked_list<job>* s = new linked_list<job>[end_clock+1];
    
    for(auto i=all_periodic_tasks.begin(); i!=all_periodic_tasks.end(); i=i->next_node){
        int pred = i->t.period;
        for(int c=0; c<=end_clock; c++){
            if(c- i->t.phase_time >= 0 && (c- i->t.phase_time)%pred == 0){
                int job_info[4] = {c , c+i->t.relative_deadline , i->t.execution_time , i->t.TID};
                s[c].push_back(job(job_info) );
            }
        }

    }

    return s;
}

template<class T> void scheduler<T>::visualize_scheduling(linked_list<job> periodic_task_schedule[], linked_list<int>&scheduled_results , int end_clock){

    for(auto i=scheduled_results.begin(); i!=scheduled_results.end(); i=i->next_node){
        if(i->t !=-1)
                std::cout<< "| T" << i->t << " ";
            else
                std::cout<< "| XX ";
    }
        
    std::cout<<"|\n";

    for(int clock = 0; clock < end_clock; clock++)
        std::cout<<"-----";
    std::cout<<"-\n";
    for(int clock = 0; clock <= end_clock; clock++)
        std::cout<<std::left <<std::setw(5)<<clock;
    std::cout<<"\n\n";
    for(int i=0;i<all_periodic_tasks.size();i++){
        for(int clock = 0; clock <= end_clock; clock++){
            if(periodic_task_schedule[clock].size() >= i+1)
                std::cout<<"T"<<periodic_task_schedule[clock][i].TID<<"   ";
            else
                std::cout<<"     ";
        }
        std::cout<<"\n";
    }

}
template<class T> void scheduler<T>::save_scheduling(linked_list<int>&scheduled_results , int end_clock , std::string filename){
    std::ofstream result(filename + ".txt");
    for(auto i=scheduled_results.begin();i!=scheduled_results.end(); i=i->next_node){
        if(i->t != -1)
            result <<"T"<< i->t <<"\t";
        else
            result << "\t";
    }
    result.close();

}
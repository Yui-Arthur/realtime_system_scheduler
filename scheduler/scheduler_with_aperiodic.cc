
#include "scheduler_with_aperiodic.h"

template<class T,class S> scheduler_with_aperiodic<T,S>::scheduler_with_aperiodic(std::string periodic_task_file, std::string aperiodic_task_file, float ap_server_size){
    read_task(periodic_task_file, 'P');
    read_task(aperiodic_task_file, 'A');
    aperiodic_server_size = ap_server_size;
};


template<class T,class S> void scheduler_with_aperiodic<T,S>::read_task(std::string task_file, char type){
    std::ifstream tasks_data(task_file); 
    std::string line_task , task_fragment;
    std::stringstream ss;
    while (std::getline(tasks_data, line_task)) {
        ss << line_task << ",";        
    }

    int cnt = 0;
    int task_info[5];
    while(std::getline(ss , task_fragment , ',')){
        task_info[cnt%2] = stoi(task_fragment);
        if(cnt%2 == 1){
            if(type == 'A')
                task_info[2] = (cnt/2) , all_aperiodic_tasks.push_back(aperiodic_task(task_info));
            else{
                // orgin 0 ->　preiod 1 -> execution_time
                // new   0 -> phase_time, 1 -> period, 2 -> relative_deadline , 3-> execution_time , 4 -> TID; 
                task_info[3] = task_info[1] ,task_info[1] = task_info[0];
                task_info[0] = 0, task_info[2] = task_info[1], task_info[4] = (cnt/2);
                this->all_periodic_tasks.push_back(periodic_task(task_info));
            }
        }

        cnt += 1;
    }
    
    tasks_data.close();

    // if (type == 'A'){
    //     std::cout << this->all_periodic_tasks;
    //     std::cout << all_aperiodic_tasks;
    // }
}

template<class T,class S> linked_list<job>* scheduler_with_aperiodic<T,S>::setting_aperiodic_task(int end_clock){
    linked_list<job>* s = new linked_list<job>[end_clock+1];
    
    for(auto i=all_aperiodic_tasks.begin(); i!=all_aperiodic_tasks.end(); i=i->next_node){
        
        if(i->t.phase_time > end_clock)
            continue;
        int job_info[4] = {i->t.phase_time, 0, i->t.execution_time, i->t.TID};
        s[i->t.phase_time].push_back(job(job_info));
    }

    return s;
}

template<class T,class S> void scheduler_with_aperiodic<T,S>::start_scheduling(){
    T scheduling(this->all_periodic_tasks);
    S aperiodic_server(aperiodic_server_size);
    if(!scheduling.schedulability_test(this->all_periodic_tasks)){
        std::cout<<"Schedulability Test Failed\n\n";
    }

    std::cout<<scheduling.scheduling_method<<"\n\n";
    int end_clock = 1000;
    linked_list<job>* periodic_task_schedule = scheduler<T>::setting_periodic_task(end_clock);
    linked_list<job>* aperiodic_task_schedule = setting_aperiodic_task(end_clock);
    linked_list<std::pair<char,int> > scheduled_results;
    int miss_deadline_cnt = 0;
    int total_periodic_job = 0;
    char current_task_type = 'A';

    // start with a empty job
    job* current_job = new job();
    for(int clock = 0; clock < end_clock; clock++){
        
        int current_miss = scheduling.check_miss_deadline(clock);
        miss_deadline_cnt += current_miss;
        // have job release in this clock
        for(auto i=periodic_task_schedule[clock].begin(); i !=periodic_task_schedule[clock].end(); i = i->next_node){
            scheduling.push_job(i->t);
            total_periodic_job += 1;
        }
        for(auto i=aperiodic_task_schedule[clock].begin(); i !=aperiodic_task_schedule[clock].end(); i = i->next_node){
            aperiodic_server.push_job(i->t);
        }
        /* when
         *   job is over 
         *   new job release
         *   current clock has miss deadline job
         *   strict check the job
         * => re-pick the highest priority job
         */ 
        // if(current_job->TID == -1 || current_job->remain_execution_time == 0 || 
        //                             periodic_task_schedule[clock].size() != 0 || current_miss != 0 || scheduling.strict){
        if(1){
            job* aperiodic_job = aperiodic_server.get_job(clock);
            job* periodic_job = scheduling.get_job(clock);
            if(aperiodic_job->absolute_deadline <= periodic_job->absolute_deadline)
                current_job = aperiodic_job, current_task_type= 'A';
            else
                current_job = periodic_job, current_task_type= 'P';                
        }
        
        current_job->remain_execution_time -= 1;

        if(current_task_type == 'A' && current_job->TID != -1)
            aperiodic_server.consume_budget();

        scheduled_results.push_back(std::make_pair(current_task_type, current_job->TID) );
        std::cout<< "Clock " << clock << " " << current_task_type <<"T" << current_job->TID+1 << "\n";
        std::cout<< "\tREM_EXET " << current_job->remain_execution_time << " DL " << current_job->absolute_deadline << "\n";

        if(current_task_type == 'A'){
            aperiodic_server.print_budget_deadline();
        }
        std::cout<<"\n";
        
    }

    visualize_scheduling(periodic_task_schedule, aperiodic_task_schedule , scheduled_results , end_clock);
    std::cout << miss_deadline_cnt << " " << float(total_periodic_job) <<"\n";
    std::cout << "Miss Rate " << miss_deadline_cnt / float(total_periodic_job) <<"\n";
    std::cout << "Response Time " <<  aperiodic_server.get_total_response_time() <<"\n";
}

template<class T,class S> void scheduler_with_aperiodic<T,S>::visualize_scheduling(linked_list<job> periodic_task_schedule[], linked_list<job> aperiodic_task_schedule[], linked_list<std::pair<char,int> >&scheduled_results , int end_clock){

    for(auto i=scheduled_results.begin(); i!=scheduled_results.end(); i=i->next_node){
        if(i->t.second !=-1)
                std::cout<< "| "<<i->t.first<< "T" << std::setw(3) << i->t.second+1 << " ";
            else
                std::cout<< "| XXXXX ";
    }
        
    std::cout<<"|\n";

    for(int clock = 0; clock < end_clock; clock++)
        std::cout<<"--------";
    std::cout<<"-\n";
    for(int clock = 0; clock <= end_clock; clock++)
        std::cout<<std::left <<std::setw(8)<<clock;
    std::cout<<"\n\n";

    int maxx = 0;
    for(int clock = 0; clock <= end_clock; clock++)
        maxx = std::max(maxx , periodic_task_schedule[clock].size() + aperiodic_task_schedule[clock].size());
    

    for(int i=0; i< maxx ;i++){
        for(int clock = 0; clock <= end_clock; clock++){
            if(periodic_task_schedule[clock].size() >= i+1)
                std::cout<<"PT"<< std::setw(3) <<periodic_task_schedule[clock][i].TID+1<<"   ";
            else if(aperiodic_task_schedule[clock].size() >= i-periodic_task_schedule[clock].size()+1)
                std::cout<<"AT"<< std::setw(3) <<aperiodic_task_schedule[clock][i-periodic_task_schedule[clock].size()].TID+1<<"   ";
            else
                std::cout<<"        ";
        }
        std::cout<<"\n";
    }
    std::cout<<"\n";

}

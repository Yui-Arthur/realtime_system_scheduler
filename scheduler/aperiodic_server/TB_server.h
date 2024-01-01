#ifndef _TBS_APERIODIC_SERVER_H_
#define _TBS_APERIODIC_SERVER_H_

#include "aperiodic_server.h"

class TB_server : public aperiodic_server{
    public:
        TB_server(float server_size) : aperiodic_server(server_size) {;};
        void push_job(job);
        job* get_job(int);
    private:
        void replenishment_1(job);
        void replenishment_2(int);
        void remove_done_job(int);

        
};

#include "TB_server.cc"

#endif
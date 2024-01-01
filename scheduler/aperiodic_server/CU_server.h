#ifndef _CUS_APERIODIC_SERVER_H_
#define _CUS_APERIODIC_SERVER_H_

#include "aperiodic_server.h"

class CU_server : public aperiodic_server{
    public:
        CU_server(float server_size) : aperiodic_server(server_size) {;};
        void push_job(job);
        job* get_job(int);
    private:
        void replenishment_1(job);
        void replenishment_2(int);

        
};

#include "CU_server.cc"

#endif
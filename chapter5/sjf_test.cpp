#include "cpu_scheduler.h"

int main(){
    list<Process> q = {
        {"p1", 0, 6}, {"p2", 0, 8}, {"P3", 0, 7}, {"P4", 0, 3}
    };
    
    sjf(q);

    list<Process> q2 = {
        {"p1", 4, 6}, {"p2", 2, 8}, {"P3", 1, 7}, {"P4", 7, 3}
    };
    sjf(q2);

    return 0;
}


#include "cpu_scheduler.h"

int main(){
    list<Process> q = {
        {"p1", 0, 8}, {"p2", 1, 4}, {"P3", 2, 9}, {"P4", 3, 5}
    };
    srtf(q);

    list<Process> q2 = {
        {"P1", 0, 8}, {"P2", 4, 7}, {"P3", 20, 3}, {"P4", 5, 2}, {"P5", 25, 4}
    };
    srtf(q2);
    return 0;
}


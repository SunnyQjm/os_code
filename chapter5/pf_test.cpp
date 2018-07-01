
#include "cpu_scheduler.h"

int main(){
    list<Process> q = {
        {"P1", 0, 10, 3}, {"P2", 0, 1, 1}, {"P3", 0, 2, 4},
        {"P4", 0, 1, 5}, {"P5", 0, 5, 2}
    };
    pf(q);

    return 0;
}


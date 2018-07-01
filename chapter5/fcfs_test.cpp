#include "cpu_scheduler.h"
int main(){
    list<Process> q = {
        {"P1", 9, 24}, {"P2", 0, 3}, {"P3", 4, 3}
    };
    fcfs(q);

    list<Process> q2 = {
        {"P1", 0, 24}, {"P2", 0, 3}, {"P3", 0, 3}
    };
    fcfs(q2);
    return 0;
}


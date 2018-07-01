#include "cpp_scheduler.h"


int main(){
    
    
    int n;          //the process num;
    list<Process> list;
    while(cin >> n){
        for(int i = 0; i < n; i++){
            Process p;
            cin >> p.name >> p.arrivalTime >> p.execTime;
            list.push_back(p);
        }
        fcfs(list);
    }
    return 0;
}


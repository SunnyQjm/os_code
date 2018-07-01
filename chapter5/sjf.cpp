#include "cpu_scheduler.h"

int main(){
    int n;          //the process num;
    list<Process> list;
    while(cin >> n){
        list.clear();
        for(int i = 0; i < n; i++){
            Process p;
            cin >> p.name >> p.arrivalTime >> p.execTime;
            list.push_back(p);
        }
        sjf(list);
    }
    return 0;
}


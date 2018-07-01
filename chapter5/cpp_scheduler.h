#include "gantout.h"
#include <algorithm>

struct Process{
    string name;
    int arrivalTime;
    int execTime;

};

const string WAIT_TAG = "*";

/**
 * 按到来时间排序的比较器。从小到大
 */
bool arrivalTimeComparator(const Process &p1, const Process &p2){
    return p1.arrivalTime < p2.arrivalTime;
}


/**
 * 将用户的输入格式化输出
 */
void printFormat(const list<Process>& l){
    cout << "\tProcess" << "\t\tArrival" << "\t\tExecTime" << endl;
    for(auto &process : l){
        cout << '\t' << process.name << "\t\t" << process.arrivalTime << "\t\t" << process.execTime << endl;
    }
    cout << endl;
}


/**
 * 获取一个调度队列所对应的平均等待时间
 */
void printAverageWaitTimeAndAverageAroundTime(const list<Task> &l, int throughTime, int totalExecTime){
    int processNum = 0;
    int totalAroundTime = 0;
    auto end = l.crend();
    for(auto iter = l.crbegin(); iter != end; iter++){
        
        if((*iter).name != WAIT_TAG && (*iter).remainTime == 0){         //忽略CPU空闲部分和未执行完的进程
            totalAroundTime += (throughTime - (*iter).arrivalTime);
            ++processNum;
        }
        throughTime -= (*iter).duration;
    }
    cout << "\t平均周转时间: " << totalAroundTime * 1.0 / processNum << endl;
    cout << "\t平均等待时间: " << (totalAroundTime - totalExecTime) * 1.0 / processNum << endl;
}

/**
 * 输入一个进程队列，输出gant图以及平均等待时间和平均周转时间
 */
void fcfs(list<Process>& l){
    cout << "-----------------------------------------------------------------" << endl;
    //先将用户的输入格式化输出
    cout << " 输入：" << endl;
    printFormat(l);
    //先按到来时间排序
    l.sort(arrivalTimeComparator);
    
    //////////////////////////////////////////////////
    /// 下面这段代码绘制出Gant图
    //////////////////////////////////////////////////
    cout << " Gant图：" << endl;
    list<Task> ts;
    int throughTime = 0;        //当前系统运行的时间
    int totalExecTime = 0;      //所有进程执行时间之和
    for(auto &process : l){
        totalExecTime += process.execTime;
        //如果在调度的时候，就绪队列为空，下一个进程还没到来，就会有一段CPU空闲没人用的时候
        if(process.arrivalTime > throughTime){  
            Task t;
            t.name = WAIT_TAG;           // * 表示无进程可调度，CPU空闲
            t.duration = process.arrivalTime - throughTime;
            ts.push_back(t);
            throughTime += t.duration;
        }
        Task t;
        t.name = process.name;
        t.duration = process.execTime;
        t.arrivalTime = process.arrivalTime;
        t.remainTime = 0;
        ts.push_back(t);
        throughTime += t.duration;
    }
    printGantGraph(ts);

    ///////////////////////////////////////////////////////
    //// 下面的代码输出性能指标，平均等待时间等等
    ///////////////////////////////////////////////////////
    cout << " 性能指标：" << endl;
    cout << endl;
    printAverageWaitTimeAndAverageAroundTime(ts, throughTime, totalExecTime);
    cout << endl;
    cout << "-----------------------------------------------------------------" << endl;
}




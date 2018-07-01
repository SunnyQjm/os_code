#include "gantout.h"
#include <algorithm>
#include <queue>

struct Process{
    string name;
    int arrivalTime;
    int execTime;
    int priority;
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
 * 输出一个调度队列所对应的平均等待时间
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
 * 根据进程的执行顺序获得任务执行列表
 *
 * 结果到list当中
 */
void getTaskList(list<Task> &ts, const list<Process> & pList, int &throughTime, int &totalExecTime){
    for(auto &process : pList){
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
   
    getTaskList(ts, l, throughTime, totalExecTime);
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


/**
 * 用于SJF算法排序的比较器定义
 * 先按到来时间排序，再按作业长短排序
 */
bool sjfComparator(const Process &p1, const Process &p2){
    if(p1.arrivalTime < p2.arrivalTime)
        return true;
    else if(p1.arrivalTime == p2.arrivalTime)
        return p1.execTime < p2.execTime;
    else
        return false;
}

/**
 * 短作业有限算法（SJF）实现
 * 非抢占
 */
void sjf(list<Process> & l){
    cout << "-----------------------------------------------------------------" << endl;    
    //先将用户的输入格式化输出
    cout << " 输入：" << endl;
    printFormat(l);
    //先按到来时间排序，再按作业长短排序
    l.sort(sjfComparator);
    //////////////////////////////////////////////////
    /// 下面这段代码绘制出Gant图
    //////////////////////////////////////////////////
    cout << " Gant图：" << endl;
    list<Task> ts;
    int throughTime = 0;        //当前系统运行的时间
    int totalExecTime = 0;      //所有进程执行时间之和
   
    getTaskList(ts, l, throughTime, totalExecTime);
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

struct srtfCmp{
    
    bool operator()(const Process &p1, const Process &p2) const{
        return p1.execTime > p2.execTime;
    }
};

/**
 * 最短生于时间算法
 *
 * 一种允许抢占的SJF算法
 */
void srtf(list<Process> &l){
    if(l.empty()){
        cout << "Not Allow Empty" << endl;
        return;
    }
    cout << "-----------------------------------------------------------------" << endl;    
    //先将用户的输入格式化输出
    cout << " 输入：" << endl;
    printFormat(l);
    //先按到来时间排序，再按作业长短排序
    l.sort(arrivalTimeComparator);
    //////////////////////////////////////////////////
    /// 下面这段代码绘制出Gant图
    //////////////////////////////////////////////////
    cout << " Gant图：" << endl;
    priority_queue<Process, vector<Process>, srtfCmp> pq; 
    list<Task> ts;
    int throughTime = 0;        //当前系统运行的时间
    int totalExecTime = 0;      //所有进程执行时间之和
   
    //先将第一个到达的进程推入队列
    Process p = l.front();
    Task t;
    t.name = p.name;
    t.duration = 0;
    t.arrivalTime = p.arrivalTime;
    totalExecTime += p.execTime;
    for(auto it = ++l.cbegin(); it != l.cend(); it++){
        Process newP = (*it);
        totalExecTime += newP.execTime;
        if(p.execTime + throughTime <= newP.arrivalTime){       //该进程在下一个进程到来前执行结束
            t.duration += p.execTime;
            t.remainTime = 0;
            ts.push_back(t);

            //当前系统运行时间推进
            throughTime += p.execTime;
            
            //判断在下一个进程到来前，是否还有能执行的进程
            //没有则插入等待时间
            while(!pq.empty() && throughTime < newP.arrivalTime){
                p = pq.top();
                pq.pop();
                if(p.execTime < (newP.arrivalTime - throughTime)){  //该进程可在下一个进程到来前执行结束
                    t.name = p.name;
                    t.arrivalTime = p.arrivalTime;
                    t.remainTime = 0;
                    t.duration = p.execTime;
                    ts.push_back(t);
                } else {
                    t.name = p.name;
                    t.arrivalTime = p.arrivalTime;
                    t.duration = newP.arrivalTime - throughTime;
                    t.remainTime = p.execTime - t.duration;
                    p.execTime -= t.duration;
                    pq.push(p);
                }
                throughTime += t.duration;
            }
            if(pq.empty() && throughTime < newP.arrivalTime){
                t.name = WAIT_TAG;
                t.duration = newP.arrivalTime - throughTime;
                ts.push_back(t);
                throughTime = newP.arrivalTime;
            }
            
            pq.push(newP);
            //从队列里选择下一个要执行的进程
            p = pq.top();
            t.name = p.name;
            t.duration = 0;
            t.arrivalTime = p.arrivalTime;
            pq.pop();
        } else if((p.execTime - (newP.arrivalTime - throughTime)) <= newP.execTime){      //当前进程比新来进程的执行剩余时间短，不被抢占
            t.duration += (newP.arrivalTime - throughTime);
            p.execTime -= (newP.arrivalTime - throughTime); //更新当前进程的剩余执行时间
            //时间往前推进
            throughTime = newP.arrivalTime;
            pq.push(newP);
        } else {        //新来进程会抢占当前正在执行的进程
            t.duration += newP.arrivalTime - throughTime;
            ts.push_back(t);

            p.execTime -= (newP.arrivalTime - throughTime);
            pq.push(p);     //没执行完，放回队列当中
            throughTime = newP.arrivalTime;
            p = newP;       //抢占进程抢到CPU开始执行
            t.name = p.name;
            t.duration = 0;
            t.arrivalTime = p.arrivalTime;
        }
    }

    // 执行至此，所有的进程都已到来
    t.duration += p.execTime;
    t.remainTime = 0;
    throughTime += p.execTime;
    ts.push_back(t);

    //遍历优先队列中剩下的进程
    //考虑可能出现CPu空闲的问题
    while(!pq.empty()){
        p = pq.top();
        pq.pop();

        if(throughTime < p.arrivalTime){    //CPU空闲，无进程可调度
            t.name = WAIT_TAG;
            t.duration = p.arrivalTime - throughTime;
            ts.push_back(t);
            throughTime = p.arrivalTime;
        }
        t.name = p.name;
        t.arrivalTime = p.arrivalTime;
        t.duration = p.execTime;
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


/**
 * 将用户的输入格式化输出(带优先级)
 */
void printUserInputWithPriority(const list<Process> &l){
    cout << "\tProcess" << "\t\tArrival" << "\t\tExecTime" << "\t\tPriority" << endl;
    for(auto &process : l){
        cout << '\t' << process.name << "\t\t" << process.arrivalTime << "\t\t" << process.execTime << "\t\t" << process.priority << endl;
    }
    
}

struct pfComparator{
    bool operator() (const Process &p1, const Process &p2) const {
        return p1.priority > p2.priority;
    }
};

bool priorityCmp(const Process &p1, const Process &p2){
    if(p1.arrivalTime < p2.arrivalTime){
        return true;
    } else if(p1.arrivalTime == p2.arrivalTime){
        return p1.priority < p2.priority;
    }
    return false;
}

/**
 * 优先级调度算法(抢占方法实现)
 */
void pf(list<Process> &l){
    if(l.empty()){
        cout << "Not Allow Empty" << endl;
        return;
    }
    cout << "-----------------------------------------------------------------" << endl;    
    //先将用户的输入格式化输出
    cout << " 输入：" << endl;
    printUserInputWithPriority(l);
    //先按到来时间排序，在按优先级从大到小排序
    l.sort(priorityCmp);
    
    //////////////////////////////////////////////////
    /// 下面这段代码绘制出Gant图
    //////////////////////////////////////////////////
    cout << " Gant图：" << endl;
    priority_queue<Process, vector<Process>, pfComparator> pq; 
    list<Task> ts;
    int throughTime = 0;
    int totalExecTime = 0;
    Process p = l.front();
    Task t;
    t.name = p.name;
    t.arrivalTime = p.arrivalTime;
    t.duration = 0;
    t.remainTime = p.execTime;
    totalExecTime += p.execTime;
    auto end = l.cend();
    for(auto it = ++l.cbegin(); it != end; ++it){
        Process newP = (*it);
        totalExecTime += newP.execTime;
        if(p.execTime + throughTime < newP.arrivalTime){    //当前进程在下一进程到来之前结束
            t.duration += p.execTime;
            t.remainTime = 0;
            ts.push_back(t);

            //当前系统运行时间向前推进
            throughTime += p.execTime;
            
            //判断在下一个进程到来前，是否还有能执行的进程
            //没有则插入等待时间
            while(!pq.empty() && throughTime < newP.arrivalTime){
                p = pq.top();
                pq.pop();
                if(p.execTime < (newP.arrivalTime - throughTime)){  //该进程可在下一个进程到来前执行结束
                    t.name = p.name;
                    t.arrivalTime = p.arrivalTime;
                    t.remainTime = 0;
                    t.duration = p.execTime;
                    ts.push_back(t);
                } else {
                    t.name = p.name;
                    t.arrivalTime = p.arrivalTime;
                    t.duration = newP.arrivalTime - throughTime;
                    t.remainTime = p.execTime - t.duration;
                    p.execTime -= t.duration;
                    pq.push(p);
                }
                throughTime += t.duration;
            }
            if(pq.empty() && throughTime < newP.arrivalTime){
                t.name = WAIT_TAG;
                t.duration = newP.arrivalTime - throughTime;
                ts.push_back(t);
                throughTime = newP.arrivalTime;
            }
            pq.push(newP);
            //从队列里选择下一个要执行的进程
            p = pq.top();
            t.name = p.name;
            t.duration = 0;
            t.arrivalTime = p.arrivalTime;
            pq.pop();

        } else if(p.priority <= newP.priority){     //当前进程比新来进程的优先级高，不被抢占
            t.duration += (newP.arrivalTime - throughTime);
            p.execTime -= (newP.arrivalTime - throughTime); //更新当前进程的剩余执行时间
            //时间往前推进
            throughTime = newP.arrivalTime;
            pq.push(newP);
        } else {    //新来进程的优先级比当前进程高，会抢占当前进程
            t.duration += newP.arrivalTime - throughTime;
            ts.push_back(t);

            p.execTime -= (newP.arrivalTime - throughTime);
            pq.push(p);     //没执行完，放回队列当中
            throughTime = newP.arrivalTime;
            p = newP;       //抢占进程抢到CPU开始执行
            t.name = p.name;
            t.duration = 0;
            t.arrivalTime = p.arrivalTime;
        } 
    }

    // 执行至此，所有的进程都已到来
    t.duration += p.execTime;
    t.remainTime = 0;
    throughTime += p.execTime;
    ts.push_back(t);

    //遍历优先队列中剩下的进程
    //考虑可能出现CPu空闲的问题
    while(!pq.empty()){
        p = pq.top();
        pq.pop();

        if(throughTime < p.arrivalTime){    //CPU空闲，无进程可调度
            t.name = WAIT_TAG;
            t.duration = p.arrivalTime - throughTime;
            ts.push_back(t);
            throughTime = p.arrivalTime;
        }
        t.name = p.name;
        t.arrivalTime = p.arrivalTime;
        t.duration = p.execTime;
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

#ifndef BASE_H
#define BASE_H
#include <iostream>
using namespace std;
#endif

#ifndef GANT_OUT_H
#define GANT_OUT_H
#include <list>
#include <string>


/**
 * 下面的结构体代表一个任务，即一个进程在CPU上的一次执行
 */
struct Task{
    string name;
    int duration;
    int arrivalTime;
    int remainTime;
};

/**
 * 输出上下边界
 */
void printBound(const list<Task> &list){
    cout << "\t+";
    int temp;
    for(auto &t : list){
        temp = t.duration + t.name.length();
        for(int j = 0; j < temp; j++){
            cout << '-';
        }
        cout << '+';

    }
    cout << endl;
}

/**
 * 输出进程标识
 */
void printTag(const list<Task> &list){
    cout << "\t|";
    int n;
    for(auto &t : list){
        n = t.duration;
        for(int j = 0; j < n / 2; j++){
            cout << ' ';
        }
        cout << t.name;
        for(int j = n / 2; j < n; j++){
            cout << ' ';
        }
        cout << '|';

    }
    cout << endl;
}


/**
 * 得到一个整数有几位数
 */
int getLenOfNum(int num){
    int result = 0;
    while(num != 0){
        result++;
        num = num / 10;
    }
    return result;
}


/**
 * 输出Gant图底部的时间点
 */
void printTimePoint(const list<Task> &list){
    cout << "\t0";
    int temp;
    int throughTimes = 0;   
    int sub = 0;
    int num_len;
    for(auto &t : list){
        throughTimes += t.duration;
        num_len = getLenOfNum(throughTimes);
        sub += (num_len / 2);
        temp = t.duration + t.name.length() - sub;
        for(int j = 0; j < temp; j++){
            cout << ' ';
        }
        cout << throughTimes;
        sub = num_len - num_len / 2 - 1;
    }
    cout << endl;
}

/**
 * 输出CPU调度的Gant图
 * 
 * times => 执行时间序列
 * tags => 每个时间段执行进程的标识
 *
 * 要求两个序列的长度是一致的
 */
void printGantGraph(const list<Task> &q){
    cout << endl;
    printBound(q);
    printTag(q);
    printBound(q);
    printTimePoint(q);
    cout << endl;
}

#endif

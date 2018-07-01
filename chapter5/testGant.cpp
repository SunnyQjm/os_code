#include "gantout.h"

int main()
{
    list<Task> q = {
        {"P1", 24, 0, 0},{"P2", 3, 0, 0}, {"P3", 3, 0, 0}
    };
    printGantGraph(q);
    
    cout << "6: " << getLenOfNum(6) << endl;
    cout << "66: " << getLenOfNum(66) << endl;
    cout << "666: " << getLenOfNum(666) << endl;
    cout << "6666: " << getLenOfNum(6666) << endl;
    cout << "66666: " << getLenOfNum(66666) << endl;
    
    return 0;
}


#include <iostream>
#include <thread>
#include <unistd.h>
using namespace std;

int count = 0;

void taskB()
{

    for (int i = 0; i < 1000; i++)
    {
        count += i;
    }
}

int main()
{
    thread t2(taskB);
    thread t3(taskB);
    t2.join();
    t3.join();

    printf("%d", count);
    return 0;
}
#include <iostream>
#include <thread>
#include <unistd.h>
using namespace std;

long long count = 0;

void taskB()
{

    for (int i = 0; i < 1000000; i++)
    {
        count += i;
    }
}

void taskA()
{

    for (int i = 1; i < 5; i++)
    {
        count *= i;
    }
}

int main()
{
    thread t2(taskB);
    thread t3(taskB);
    t2.join();
    t3.join();

    printf("%lld", count);
    return 0;
}
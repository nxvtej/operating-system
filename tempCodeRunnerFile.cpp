#include <iostream>
#include <thread>
#include <unistd.h>
using namespace std;

void taskA()
{

    for (int i = 0; i < 10; i++)
    {
        sleep(1);
        printf("TaskA: %d\n", i);
        fflush(stdout);
    }
}
void taskB()
{

    for (int i = 0; i < 10; i++)
    {
        sleep(1);
        printf("TaskB: %d\n", i);
        fflush(stdout);
    }
}

int main()
{
    thread t1(taskA);
    thread t2(taskB);
    thread t3(taskB);
    thread t4(taskB);
    thread t5(taskB);
    thread t6(taskB);
    // if executed like this
    // it wont work i have to make the
    // parent wait for its childrens to
    // exit that can be done with join

    t1.join();
    // t2.join();

    /*
    output will be
    TaskA: 0
TaskB: 0
TaskA: 1
TaskB: 1
TaskA: 2
TaskB: 2
TaskB: 3
TaskA: 3
TaskB: 4
TaskA: 4
TaskB: 5
TaskA: 5

*/
    return 0;
}
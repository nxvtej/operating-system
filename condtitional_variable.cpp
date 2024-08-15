#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

long long count = 0;
mutex mtx;
condition_variable cv;
bool ready = false; // Condition flag

void taskB()
{
    for (int i = 0; i < 1000000; i++)
    {
        count += i;
    }
    {
        lock_guard<mutex> lock(mtx);
        ready = true; // Signal that the task is complete
    }
    cv.notify_one(); // Notify one waiting thread
}

void taskA()
{
    unique_lock<mutex> lock(mtx);
    cv.wait(lock, []
            { return ready; }); // Wait until ready becomes true
    // Perform some action after taskB is done
    printf("Count is: %lld\n", count);
}

int main()
{
    thread t2(taskB);
    thread t1(taskA);

    t2.join();
    t1.join();

    return 0;
}

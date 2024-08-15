#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

int sharedData = 0; // Shared variable
mutex mtx;          // Mutex to protect access to sharedData

void increment(int id)
{
    for (int i = 0; i < 1000; ++i)
    {
        lock_guard<mutex> lock(mtx); // Lock the mutex
        ++sharedData;                // Increment the shared variable
    }
    cout << "Thread " << id << " finished incrementing." << endl;
}

int main()
{
    thread t1(increment, 1);
    thread t2(increment, 2);

    t1.join();
    t2.join();

    cout << "Final value of sharedData: " << sharedData << endl;

    return 0;
}

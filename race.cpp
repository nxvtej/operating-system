#include <iostream>
#include <thread>
#include <mutex> // Include mutex for synchronization
using namespace std;

long long count = 0;
mutex mtx; // Declare a mutex

void taskB()
{
    for (int i = 0; i < 1000000; i++)
    {
        lock_guard<mutex> lock(mtx); // Lock the mutex
        count += i;                  // Safely update the shared variable
    }
}

int main()
{
    thread t2(taskB);
    thread t3(taskB);
    t2.join();
    t3.join();

    printf("%lld\n", count); // Print the result
    return 0;
}

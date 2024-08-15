#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

int sharedData = 0;     // Shared variable
bool dataReady = false; // Flag to indicate if data is ready
mutex mtx;              // Mutex to protect access to sharedData and dataReady
condition_variable cv;  // Condition variable for synchronization

void producer()
{
    {
        lock_guard<mutex> lock(mtx); // Lock the mutex
        sharedData = 42;             // Set the shared data
        dataReady = true;            // Indicate that data is ready
    }
    cv.notify_one(); // Notify one waiting thread
}

void consumer()
{
    unique_lock<mutex> lock(mtx); // Lock the mutex
    cv.wait(lock, []
            { return dataReady; });                  // Wait until dataReady is true
    cout << "Data received: " << sharedData << endl; // Use the data
}

int main()
{
    thread prod(producer);
    thread cons(consumer);

    prod.join();
    cons.join();

    return 0;
}

#include <iostream>
#include <thread>
#include <boost/interprocess/sync/interprocess_semaphore.hpp>

using namespace std;
using namespace boost::interprocess;

interprocess_semaphore sem(1); // Create a binary semaphore (initial count = 1)

void worker(int id)
{
    cout << "Thread " << id << " is waiting for the semaphore." << endl;
    sem.wait(); // Wait (decrement the semaphore count)

    cout << "Thread " << id << " acquired the semaphore." << endl;
    this_thread::sleep_for(chrono::seconds(1)); // Simulate some work

    cout << "Thread " << id << " is releasing the semaphore." << endl;
    sem.post(); // Signal (increment the semaphore count)
}

int main()
{
    thread t1(worker, 1);
    thread t2(worker, 2);
    thread t3(worker, 3);

    t1.join();
    t2.join();
    t3.join();

    return 0;
}

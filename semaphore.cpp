#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

class Semaphore
{
public:
    Semaphore(int count) : count(count) {}

    void wait()
    {
        unique_lock<mutex> lock(mtx);
        cv.wait(lock, [this]
                { return count > 0; }); // Wait until count > 0
        --count;                        // Decrement the count
    }

    void signal()
    {
        unique_lock<mutex> lock(mtx);
        ++count;         // Increment the count
        cv.notify_one(); // Notify one waiting thread
    }

private:
    mutex mtx;             // Mutex for protecting the count
    condition_variable cv; // Condition variable for synchronization
    int count;             // Semaphore count
};

Semaphore sem(1); // Create a semaphore with an initial count of 1

void worker(int id)
{
    cout << "Thread " << id << " is waiting for the semaphore." << endl;
    sem.wait(); // Wait (decrement the semaphore count)

    cout << "Thread " << id << " acquired the semaphore." << endl;
    this_thread::sleep_for(chrono::seconds(1)); // Simulate some work

    cout << "Thread " << id << " is releasing the semaphore." << endl;
    sem.signal(); // Signal (increment the semaphore count)
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

/*

#include <iostream>
#include <thread>
#include <semaphore> // C++20 header for semaphores

using namespace std;

semaphore sem(1); // Create a binary semaphore (initial count = 1)

void worker(int id) {
    cout << "Thread " << id << " is waiting for the semaphore." << endl;
    sem.acquire(); // Wait (decrement the semaphore count)

    cout << "Thread " << id << " acquired the semaphore." << endl;
    this_thread::sleep_for(chrono::seconds(1)); // Simulate some work

    cout << "Thread " << id << " is releasing the semaphore." << endl;
    sem.release(); // Signal (increment the semaphore count)
}

int main() {
    thread t1(worker, 1);
    thread t2(worker, 2);
    thread t3(worker, 3);

    t1.join();
    t2.join();
    t3.join();

    return 0;
}


 */
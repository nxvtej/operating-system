#include <iostream>
#include <thread>
#include <semaphore>
#include <queue>
#include <mutex>

using namespace std;

constexpr int maxQueueSize = 10;                           // Maximum size of the queue
queue<int> dataQueue;                                      // Shared queue between producer and consumer
mutex mtx;                                                 // Mutex to protect access to the queue
counting_semaphore<maxQueueSize> emptySlots(maxQueueSize); // Semaphore for empty slots
counting_semaphore<0> filledSlots(0);                      // Semaphore for filled slots

void producer()
{
    for (int i = 0; i < 20; ++i)
    {
        emptySlots.acquire(); // Wait for an empty slot
        {
            lock_guard<mutex> lock(mtx); // Lock the mutex
            dataQueue.push(i);           // Produce data
            cout << "Produced: " << i << endl;
        }
        filledSlots.release();                             // Signal that data is available
        this_thread::sleep_for(chrono::milliseconds(100)); // Simulate work
    }
}

void consumer()
{
    while (true)
    {
        filledSlots.acquire(); // Wait for filled slot
        int data;
        {
            lock_guard<mutex> lock(mtx); // Lock the mutex
            if (dataQueue.empty())
            {
                filledSlots.release(); // Release if no data to process
                break;                 // Exit the loop if queue is empty and consumer is done
            }
            data = dataQueue.front(); // Consume data
            dataQueue.pop();
            cout << "Consumed: " << data << endl;
        }
        emptySlots.release();                              // Signal that there is an empty slot
        this_thread::sleep_for(chrono::milliseconds(150)); // Simulate work
    }
}

int main()
{
    thread prodThread(producer);
    thread consThread(consumer);

    prodThread.join();
    consThread.join();

    return 0;
}

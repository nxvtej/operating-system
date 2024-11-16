// #include <iostream>
// #include <queue>
// #include <thread>
// #include <chrono>

// std::queue<int> buffer; // Shared buffer
// const int MAX_BUFFER_SIZE = 5;

// void producer()
// {
//     int item = 0;
//     while (true)
//     {
//         if (buffer.size() < MAX_BUFFER_SIZE)
//         {
//             buffer.push(item); // Add item to buffer
//             std::cout << "Produced: " << item << std::endl;
//             item++; // Produce the next item
//         }
//         else
//         {
//             std::cout << "Buffer full. Producer waiting..." << std::endl;
//         }
//         std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // Slow down production
//     }
// }

// void consumer()
// {
//     while (true)
//     {
//         if (!buffer.empty())
//         {
//             int item = buffer.front();
//             buffer.pop(); // Remove item from buffer
//             std::cout << "Consumed: " << item << std::endl;
//         }
//         else
//         {
//             std::cout << "Buffer empty. Consumer waiting..." << std::endl;
//         }
//         std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // Slow down consumption
//     }
// }

// int main()
// {
//     std::thread producerThread(producer);
//     std::thread consumerThread(consumer);

//     producerThread.join();
//     consumerThread.join();

//     return 0;
// }

#include <iostream>
#include <queue>
#include <thread>
#include <semaphore.h>
#include <chrono>

std::queue<int> buffer;
const int MAX_BUFFER_SIZE = 5;

sem_t emptySlots; // Semaphore for empty slots
sem_t fullSlots;  // Semaphore for full slots

void producer()
{
    int item = 0;
    while (true)
    {
        sem_wait(&emptySlots); // Wait for an empty slot
        buffer.push(item);     // Add item to buffer
        std::cout << "Produced: " << item << std::endl;
        item++;
        sem_post(&fullSlots);                                         // Signal a full slot
        std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // Slow down production
    }
}

void consumer()
{
    while (true)
    {
        sem_wait(&fullSlots); // Wait for a full slot
        int item = buffer.front();
        buffer.pop(); // Remove item from buffer
        std::cout << "Consumed: " << item << std::endl;
        sem_post(&emptySlots);                                        // Signal an empty slot
        std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // Slow down consumption
    }
}

int main()
{
    sem_init(&emptySlots, 0, MAX_BUFFER_SIZE); // Initialize empty slots to MAX_BUFFER_SIZE
    sem_init(&fullSlots, 0, 0);                // Initialize full slots to 0

    std::thread producerThread(producer);
    std::thread consumerThread(consumer);

    producerThread.join();
    consumerThread.join();

    sem_destroy(&emptySlots);
    sem_destroy(&fullSlots);

    return 0;
}

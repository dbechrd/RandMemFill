// Copyright dbechrd - Oct 13, 2020
// Simple test to fill a large chunk of memory with random integers using C++ threads
// Written while watching https://www.twitch.tv/derrikcreates's "Learning C++ stream"

#include <iostream>
#include <sstream>
#include <thread>
#include <chrono>
#include <vector>

#define KB(x) (1024ll * (x))
#define MB(x) (1024ll * KB(x))
#define GB(x) (1024ll * MB(x))

#define BUFFER_SIZE GB(1)
#define THREAD_COUNT 4

void FillChunk(int id, int *arr, size_t length)
{
    std::stringstream ss;
    ss << "Thread " << id << " start: " << arr << " length: " << length << std::endl;
    std::cout << ss.str();

    size_t i = 0;
    for (int i = 0; i < length; i++) {
        arr[i] = rand();
    }
}

int main()
{
    auto largeDataLength = BUFFER_SIZE;
    int *largeData = new int[largeDataLength];

    const int threadCount = THREAD_COUNT;
    std::vector<std::thread> threads;

    auto start = std::chrono::high_resolution_clock::now();

    auto chunkLength = largeDataLength / threadCount;
    int *start_addr = largeData;
    for (int i = 0; i < threadCount; i++) {
        threads.push_back(std::thread(FillChunk, i, start_addr, chunkLength));
        start_addr += chunkLength;
    }
    for (int i = 0; i < threadCount; i++) {
        threads[i].join();
    }

    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;

    delete[] largeData;
    std::cout << "Finished in " << elapsed.count() << " seconds." << std::endl;
    std::cin.get();
}
// Copyright dbechrd - Oct 13, 2020
// Simple test to fill a large chunk of memory with random integers using C++ threads
// Written while watching https://www.twitch.tv/derrikcreates's "Learning C++ stream"

#include <iostream>
#include <sstream>
#include <thread>
#include <chrono>

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

    for (size_t i = 0; i < length; i++) {
        arr[i] = rand();
    }
}

int main()
{
    std::thread threads[THREAD_COUNT];
    int *data = new int[BUFFER_SIZE];
    int *startAddr = data;
    auto chunkLength = BUFFER_SIZE / THREAD_COUNT;

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < THREAD_COUNT; i++) {
        threads[i] = std::thread(FillChunk, i, startAddr, chunkLength);
        startAddr += chunkLength;
    }
    for (int i = 0; i < THREAD_COUNT; i++) {
        threads[i].join();
    }

    auto finish = std::chrono::high_resolution_clock::now();

    delete[] data;
    std::cout << "Finished in " << (finish - start).count() << " seconds." << std::endl;
    std::cin.get();
}
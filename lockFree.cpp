#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <chrono>
#include <atomic>

std::mutex mtx; // Mutex for protecting access to the counter
int counter = 0; // Shared counter

void incrementWithLock(int n) {
    for (int i = 0; i < n; ++i) {
        std::lock_guard<std::mutex> lock(mtx);
        ++counter;
    }
}

std::atomic<int> atomicCounter(0); // Shared atomic counter

void incrementLockFree(int n) {
    for (int i = 0; i < n; ++i) {
        atomicCounter.fetch_add(1, std::memory_order_relaxed);
    }
}

int main() {
    int sampleCount = 15;
    std::chrono::duration<double> totalNonLockFree, totalLockFree;
    for (int i = 0; i < sampleCount; i++){
    
    const int incrementsPerThread = 100000;
    const int threadCount = 4;

    // Non-lock-free version
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<std::thread> threads;
    for (int i = 0; i < threadCount; ++i) {
        threads.push_back(std::thread(incrementWithLock, incrementsPerThread));
    }
    for (auto& t : threads) t.join();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    totalNonLockFree += duration;
    std::cout << "Non-lock-free version time: " << duration.count() << "s\n";

    // Reset counter
    counter = 0;
    threads.clear();

    // Lock-free version
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < threadCount; ++i) {
        threads.push_back(std::thread(incrementLockFree, incrementsPerThread));
    }
    for (auto& t : threads) t.join();
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    totalLockFree += duration;
    std::cout << "Lock-free version time: " << duration.count() << "s\n";
    }
    auto averageNonLockFree = totalNonLockFree / sampleCount;
    auto averageLockFree = totalLockFree / sampleCount;
    std::cout << "Average Non-lock-free version time over " << sampleCount << " executions: " << averageNonLockFree.count() << "\n";
    std::cout << "Average Lock-free version time over " << sampleCount << " executions: " << averageLockFree.count() << "\n";
    return 0;

}

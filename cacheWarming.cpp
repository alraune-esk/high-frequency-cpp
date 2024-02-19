#include <iostream>
#include <vector>
#include <chrono>

const size_t ARRAY_SIZE = 1000000000; // Large array to increase the chance of cache misses
std::vector<int> data(ARRAY_SIZE);

// Function to "warm" the cache by accessing elements of the array
void warmCache() {
    for (size_t i = 0; i < ARRAY_SIZE; i += 64) { // Access strides to simulate realistic usage and ensure not all data is cached
        volatile int tmp = data[i]; // Volatile to prevent compiler optimizations removing the read
    }
}

// Function to measure access time of the array elements
long long measureAccessTime(bool warmCacheFirst) {
    if (warmCacheFirst) {
        warmCache(); // Warm the cache if requested
    }

    auto start = std::chrono::high_resolution_clock::now();

    long long sum = 0;
    for (size_t i = 0; i < ARRAY_SIZE; ++i) {
        sum += data[i];
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;

    return duration.count();
}

int main() {
    // Average over this many executions
    int sampleCount = 10; 
    // Fill the array with some data
    std::fill(data.begin(), data.end(), 1);
    // Total times
    double totalCacheCold;
    double totalCacheWarm;

    for (int i = 0; i < sampleCount; i++)
    {
     // Measure access time without cache warming
    auto timeWithoutCacheWarming = measureAccessTime(false);
    totalCacheCold += timeWithoutCacheWarming;
    std::cout << "Access time without cache warming: " << timeWithoutCacheWarming << " ms\n";

    // Measure access time with cache warming
    auto timeWithCacheWarming = measureAccessTime(true);
    totalCacheWarm += timeWithCacheWarming;
    std::cout << "Access time with cache warming: " << timeWithCacheWarming << " ms\n";
    }

    std::cout << "Average time without cache warming over " << sampleCount << " executions: " << totalCacheCold / sampleCount << "\n";
    std::cout << "Average time with cache warming over " << sampleCount << " executions: " << totalCacheWarm / sampleCount << "\n";

    return 0;
}

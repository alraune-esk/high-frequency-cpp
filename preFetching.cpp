#include <iostream>
#include <vector>
#include <chrono>
#include <xmmintrin.h> // For _mm_prefetch

const int ARRAY_SIZE = 100000000; // Large enough to exceed cache sizes
const int STRIDE = 256; // Large stride to simulate non-sequential access

// Initializes the vector with dummy data
void initialize(std::vector<int>& vec) {
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        vec[i] = i;
    }
}

// Non-prefetching version
long long sumNonPrefetching(const std::vector<int>& vec) {
    long long sum = 0;
    for (int i = 0; i < ARRAY_SIZE; i += STRIDE) {
        sum += vec[i];
    }
    return sum;
}

// Prefetching version
long long sumPrefetching(const std::vector<int>& vec) {
    long long sum = 0;
    for (int i = 0; i < ARRAY_SIZE; i += STRIDE) {
        // Prefetch data that is STRIDE * 4 bytes ahead
        _mm_prefetch((const char*)&vec[i + STRIDE], _MM_HINT_T0);
        sum += vec[i];
    }
    return sum;
}

template<typename Func>
double measureExecutionTime(Func func, const std::vector<int>& vec) {
    auto start = std::chrono::high_resolution_clock::now();
    func(vec);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;
    return duration.count();
}

int main() {
    std::vector<int> vec(ARRAY_SIZE);
    initialize(vec);
    int sampleCount = 10;
    double totalNPF, totalPF;

    for (int i = 0; i < sampleCount; i++)
    {
    double timeNPF = measureExecutionTime(sumNonPrefetching, vec);
    totalNPF += timeNPF;
    std::cout << "Non-Prefetching execution time: " << timeNPF << " milliseconds\n";

    double timePF = measureExecutionTime(sumPrefetching, vec);
    totalPF += timePF;
    std::cout << "Prefetching execution time: " << timePF << " milliseconds\n";
    }

    std::cout << "Average time without Prefetching over " << sampleCount << " executions: " << totalNPF / sampleCount << "\n";
    std::cout << "Average time with Prefetching over " << sampleCount << " executions: " << totalPF / sampleCount << "\n";


    return 0;
}

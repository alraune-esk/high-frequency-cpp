#include <iostream>
#include <vector>
#include <chrono>
#include <xmmintrin.h> // SSE intrinsics

// Non-SIMD version
void addArraysNonSIMD(const std::vector<float>& a, const std::vector<float>& b, std::vector<float>& result) {
    for (size_t i = 0; i < a.size(); ++i) {
        result[i] = a[i] + b[i];
    }
}

// SIMD version using SSE
void addArraysSIMD(const std::vector<float>& a, const std::vector<float>& b, std::vector<float>& result) {
    size_t i = 0;
    // Process four floats per iteration with SSE
    for (; i + 3 < a.size(); i += 4) {
        __m128 aVec = _mm_loadu_ps(&a[i]); // Load 4 floats from array a
        __m128 bVec = _mm_loadu_ps(&b[i]); // Load 4 floats from array b
        __m128 resultVec = _mm_add_ps(aVec, bVec); // Add them
        _mm_storeu_ps(&result[i], resultVec); // Store the result
    }
    // Handle remaining elements
    for (; i < a.size(); ++i) {
        result[i] = a[i] + b[i];
    }
}

template<typename Func>
double measureExecutionTime(Func func, const std::vector<float>& a, const std::vector<float>& b, std::vector<float>& result) {
    auto start = std::chrono::high_resolution_clock::now();
    func(a, b, result); // Execute the function
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;
    return duration.count();
}

int main() {
    const size_t ARRAY_SIZE = 10000000;
    std::vector<float> a(ARRAY_SIZE, 1.0f); // Initialized with 1.0
    std::vector<float> b(ARRAY_SIZE, 2.0f); // Initialized with 2.0
    std::vector<float> result(ARRAY_SIZE, 0.0f);
    int sampleCount = 10;
    double totalNonSIMD; 
    double totalSIMD;

    for (int i = 0; i < sampleCount; i++)
    {
    double timeNonSIMD = measureExecutionTime(addArraysNonSIMD, a, b, result);
    totalNonSIMD += timeNonSIMD;
    std::cout << "Non-SIMD execution time: " << timeNonSIMD << " milliseconds\n";

    double timeSIMD = measureExecutionTime(addArraysSIMD, a, b, result);
    totalSIMD += timeSIMD;
    std::cout << "SIMD execution time: " << timeSIMD << " milliseconds\n";
    }

    std::cout << "Average time without SIMD over " << sampleCount << " executions: " << totalNonSIMD / sampleCount << "\n";
    std::cout << "Average time with SIMD over " << sampleCount << " executions: " << totalSIMD / sampleCount << "\n";

    return 0;
}

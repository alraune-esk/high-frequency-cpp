#include <iostream>
#include <vector>
#include <chrono>

template<typename T>
void fillVector(std::vector<T>& vec, T startValue) {
    T value = startValue;
    for (auto& elem : vec) {
        elem = value++;
    }
}

template<typename T>
void performDivision(std::vector<T>& vec, T divisor) {
    for (auto& elem : vec) {
        elem = elem / divisor;
    }
}

template<typename T>
double measureExecutionTime(std::vector<T>& vec, T divisor) {
    auto startTime = std::chrono::high_resolution_clock::now();
    performDivision(vec, divisor);
    auto endTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = endTime - startTime;
    return duration.count();
}

int main() {
    const size_t VECTOR_SIZE = 10000000;
    std::vector<int> signedVec(VECTOR_SIZE);
    std::vector<unsigned int> unsignedVec(VECTOR_SIZE);
    // Ensure divisor is of a type that matches the vector element type in each call
    int signedDivisor = 3; // Use int for the signed vector
    unsigned int unsignedDivisor = 3; // Use unsigned int for the unsigned vector

    fillVector(signedVec, static_cast<int>(-static_cast<int>(VECTOR_SIZE) / 2));
    fillVector(unsignedVec, 0u);
    int sampleCount = 10;
    double totalSignedTime, totalUnsignedTime;

    for (int i = 0; i < sampleCount; i++)
    {
    // Call measureExecutionTime with matching divisor types
    double signedTime = measureExecutionTime(signedVec, signedDivisor);
    totalSignedTime += signedTime;
    std::cout << "Signed division execution time: " << signedTime << " milliseconds\n";

    double unsignedTime = measureExecutionTime(unsignedVec, unsignedDivisor);
    totalUnsignedTime += unsignedTime;
    std::cout << "Unsigned division execution time: " << unsignedTime << " milliseconds\n";
    }
    
    std::cout << "Average time with Unsigned INT over " << sampleCount << " executions: " << totalUnsignedTime / sampleCount << "\n";
    std::cout << "Average time with Signed INT over " << sampleCount << " executions: " << totalSignedTime / sampleCount << "\n";

    return 0;
}

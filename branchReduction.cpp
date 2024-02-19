#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <random>

// Fills the vector with values and randomly shuffles it
void prepareData(std::vector<int>& data) {
    std::random_device rd;
    std::mt19937 g(rd());
    for (size_t i = 0; i < data.size(); ++i) {
        data[i] = i % 100; // Fill with values [0, 99]
    }
    std::shuffle(data.begin(), data.end(), g); // Shuffle to ensure random distribution
}

// Non-Branch Reduction: Uses an if-statement to count elements greater than a threshold
size_t countIf(const std::vector<int>& data, int threshold) {
    size_t count = 0;
    for (int value : data) {
        if (value > threshold) {
            ++count;
        }
    }
    return count;
}

// Branch Reduction: Avoids branching by using arithmetic to count elements
size_t countArithmetic(const std::vector<int>& data, int threshold) {
    size_t count = 0;
    for (int value : data) {
        count += (value > threshold); // Implicitly converts boolean to size_t (0 or 1)
    }
    return count;
}

template<typename Func>
double measureExecutionTime(Func func, const std::vector<int>& data, int threshold) {
    auto start = std::chrono::high_resolution_clock::now();
    func(data, threshold); // Execute the function
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;
    return duration.count();
}

int main() {
    const size_t DATA_SIZE = 10000000; // 10 million elements
    std::vector<int> data(DATA_SIZE);
    int sampleCount = 10;
    double totalBranchReduction;
    double totalNonBranchReduction;
    prepareData(data);
    
    for (int i = 0; i < sampleCount; i++)
    {
    double timeIf = measureExecutionTime(countIf, data, 50);
    totalNonBranchReduction += timeIf;
    std::cout << "Execution time with if-statement: " << timeIf << " milliseconds\n";

    double timeArithmetic = measureExecutionTime(countArithmetic, data, 50);
    totalBranchReduction += timeArithmetic;
    std::cout << "Execution time with arithmetic: " << timeArithmetic << " milliseconds\n";
    }

    std::cout << "Average time without Branch Reduction over " << sampleCount << " executions: " << totalNonBranchReduction / sampleCount << "\n";
    std::cout << "Average time with Branch Reduction over " << sampleCount << " executions: " << totalBranchReduction / sampleCount << "\n";


    return 0;
}

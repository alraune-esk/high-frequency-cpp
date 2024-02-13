#include <iostream>
#include <map>
#include <string>
#include <random>

// Function to generate random latency between min and max values
int randomLatency(int min, int max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(min, max);
    return dis(gen);
}

// int main() {
//     // Map to store city names and their respective latencies to Australia (in milliseconds)
//     std::map<std::string, int> cityLatencies = {
//         {"New York", 160},
//         {"London", 330},
//         {"Tokyo", 50},
//         {"Singapore", 100},
//         {"Hong Kong", 90},
//         {"Dubai", 240},
//         {"Sydney", 0}, // Australia (destination)
//         {"Paris", 310},
//         {"Berlin", 340},
//         {"Los Angeles", 190}
//     };

//     const int daysInWeek = 7;
//     const int minutesInDay = 24 * 60; // 24 hours * 60 minutes

//     // Simulate latency to Australia from each city for each minute of the week
//     std::cout << "Latency to Australia (Sydney) from major cities around the world for each minute of the week:" << std::endl;
//     for (int day = 0; day < daysInWeek; day++) {
//         for (int minute = 0; minute < minutesInDay; minute++) {
//             std::cout << "Day " << (day + 1) << ", Minute " << minute << ":" << std::endl;
//             for (const auto& city : cityLatencies) {
//                 int latency = city.second + randomLatency(1, 10); // Add random fluctuation
//                 std::cout << city.first << ": " << latency << " ms" << std::endl;
//             }
//             std::cout << std::endl;
//         }
//     }

//     return 0;
// }

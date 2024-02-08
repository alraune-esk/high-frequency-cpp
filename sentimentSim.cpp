#include <iostream>
#include <random>
#include <ctime>
#include <chrono>
#include <vector>

// Function to generate random sentiment score
int generateSentiment() {
    static std::mt19937 mt(std::time(nullptr)); // Mersenne Twister pseudo-random number generator
    static std::uniform_int_distribution<int> dist(-100, 100); // Uniform distribution from -100 to 100

    // Generate random sentiment score
    return dist(mt);
}

int main() {
    // Define weekdays and trading hours
    const std::vector<std::string> weekdays = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday"};
    const std::chrono::hours trading_hours_start(10); // Trading hours start at 10 am
    const std::chrono::hours trading_hours_end(16);   // Trading hours end at 4 pm
    const std::chrono::minutes interval(30);          // Generate sentiment every 30 minutes

    // Loop over each weekday
    for (const auto& weekday : weekdays) {
        std::cout << "----- " << weekday << " -----" << std::endl;

        // Calculate the number of intervals within trading hours for the current day
        int num_intervals = (trading_hours_end - trading_hours_start) / interval;

        // Loop over each 30-minute interval during trading hours
        std::chrono::hours current_hour = trading_hours_start;
        for (int i = 0; i < num_intervals; i++) {
            // Print the current time
            std::cout << "Time: " << current_hour.count() << ":00" << std::endl;

            // Generate sentiment for 10 different stocks
            for (int j = 0; j < 10; j++) {
                int sentiment = generateSentiment();
                std::cout << "Stock " << j + 1 << " Sentiment: " << sentiment << std::endl;
            }

            // Increment the current hour by 30 minutes
            current_hour = current_hour + std::chrono::duration_cast<std::chrono::hours>(interval);
            
        }
    }

    return 0;
}

#include <vector>
#include <string>

// Structure to represent a country with its latency
struct CountryLatency {
    std::string country;
    int latency;

    CountryLatency(const std::string& c, int l) : country(c), latency(l) {}
};

// Function to generate random network latency values for 10 different countries
std::vector<CountryLatency> generateLatencies();

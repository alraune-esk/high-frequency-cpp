#include <vector>
#include <string>

// Structure to represent a stock
struct Stock {
    std::string name;
    double price;

    Stock(const std::string& n, double p) : name(n), price(p) {}
};

// Function to generate stock prices for 20 different stocks
std::vector<Stock> generateStockPrices();

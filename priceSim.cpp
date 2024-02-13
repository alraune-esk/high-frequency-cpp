

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

// Structure to represent a stock
struct Stock {
    std::string name;
    double price;

    Stock(const std::string& n, double p) : name(n), price(p) {}
};

// Function to generate stock prices for 20 different stocks
std::vector<Stock> generateStockPrices() {
    // List of stock names
    std::vector<std::string> stockNames = {"AAPL", "MSFT", "GOOGL", "AMZN", "FB", "TSLA", "NVDA", "INTC", "AMD", "NFLX", 
                                            "ADBE", "PYPL", "CSCO", "CRM", "ORCL", "IBM", "QCOM", "V", "DIS", "JPM"};

    std::vector<Stock> stocks;
    srand(time(nullptr));
    for (const auto& name : stockNames) {
        // Generate random price between 100 and 500
        double price = (rand() % 401) + 100;
        stocks.emplace_back(name, price);
    }

    return stocks;
}

// // Function to generate a random floating-point number between min and max
// double randomDouble(double min, double max) {
//     static std::random_device rd;
//     static std::mt19937 gen(rd());
//     std::uniform_real_distribution<> dis(min, max);
//     return dis(gen);
// }

// int main() {
//     const int daysInWeek = 7;
//     const int numStocks = 10;
//     std::vector<std::string> stockNames = {"AAPL", "GOOGL", "MSFT", "AMZN", "FB", "NFLX", "TSLA", "NVDA", "AMD", "INTC"};
//     std::vector<std::vector<double>> stockPrices(numStocks, std::vector<double>(daysInWeek));

//     std::cout << "Generated stock prices for the week:" << std::endl;

//     // Generate random stock prices for each stock for each day of the week
//     for (int stockIndex = 0; stockIndex < numStocks; stockIndex++) {
//         std::cout << "Stock: " << stockNames[stockIndex] << std::endl;
//         for (int day = 0; day < daysInWeek; day++) {
//             double price = randomDouble(50.0, 200.0); // Assuming stock prices range between 50 and 200
//             stockPrices[stockIndex][day] = price;
//             std::cout << "Day " << (day + 1) << ": $" << price << std::endl;
//         }
//         std::cout << std::endl;
//     }

//     return 0;
// }

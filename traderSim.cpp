#include <iostream>
#include <vector>

using namespace std;

class HighFrequencyTrading {
private:
    vector<double> prices;  // Store historical prices
    double cash;            // Available cash
    double position;        // Current position (negative for short, positive for long)

public:
    HighFrequencyTrading(double initialCash) : cash(initialCash), position(0.0) {}

    void updatePrice(double newPrice) {
        prices.push_back(newPrice);
    }

    void trade() {
        if (prices.size() < 2) {
            cout << "Insufficient data for trading\n";
            return;
        }

        double currentPrice = prices.back();
        double previousPrice = prices[prices.size() - 2];

        // Simple strategy: Buy if price rises, sell if price falls
        if (currentPrice > previousPrice) {
            // Buy
            double amountToBuy = cash / currentPrice;  // Invest all available cash
            cash -= amountToBuy * currentPrice;        // Deduct cash used for buying
            position += amountToBuy;                    // Increase position
            cout << "Bought " << amountToBuy << " units at price " << currentPrice << endl;
        } else if (currentPrice < previousPrice) {
            // Sell
            double amountToSell = position;  // Sell all current position
            cash += amountToSell * currentPrice;  // Add cash from selling
            position = 0;                        // Reset position
            cout << "Sold " << amountToSell << " units at price " << currentPrice << endl;
        } else {
            cout << "No trade made, price remains the same\n";
        }
    }

    void printStatus() {
        cout << "Cash: $" << cash << ", Position: " << position << " units\n";
    }
};

int main() {
    HighFrequencyTrading trader(10000.0); // Initial cash: $10,000

    // Simulate price updates
    vector<double> simulatedPrices = {100.0, 102.0, 98.0, 105.0, 101.0, 200.0, 110.0, 210.0, 130.0, 203.0, 120.0};
    for (double price : simulatedPrices) {
        trader.updatePrice(price);
        trader.trade();
        trader.printStatus();
    }

    return 0;
}

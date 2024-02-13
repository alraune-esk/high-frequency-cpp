#include <iostream>
#include <vector>
#include <chrono>
#include <latencySim.h>
#include <priceSim.h>


using namespace std;

int counter;
bool checkA(){
    counter++;
    return (counter % 10) == 0;
}
bool checkB(){
    return false;
}
bool checkC(){
    return false;
}
bool checkD(){
    return false;
}
bool checkE(){
    return false;
}
bool checkF(){
    return false;
}
bool checkG(){
    return false;
}

void handleErrorA(){

}
void handleErrorB(){
    
}
void handleErrorC(){
    
}
void handleErrorD(){
    
}
void handleErrorE(){
    
}
void handleErrorF(){
    
}
void handleErrorG(){
    
}



void hotPath(){

}

static void branching(){
    counter = 0;
    for(int i = 0; i < 1000000; i++)
    {
        if(checkA()){
            handleErrorA();
        }
        else if(checkB()){
            handleErrorB();
        }
        else if(checkC()){
            handleErrorC();
        }
        else if(checkD()){
            handleErrorD();
        }
        else if(checkE()){
            handleErrorE();
        }
        else if(checkF()){
            handleErrorF();
        }
        else if(checkG()){
            handleErrorG();
        }
        else{
            hotPath();
        }
    }

}

int checkAll(){
    counter++;
    return(counter % 10) == 0 ? 1 : 0;
}

void handleAll(int flag){
    if(flag == 1){
        handleErrorA();
    }
}

static void reducedBranching(){
    counter = 0;
    for(int i = 0; i < 1000000; i++){
        int flag = checkAll();
        if(flag){
            handleAll(flag);
        }
        else{
            hotPath();
        }
    }

}



// Function to determine whether to buy, sell, or hold based on a moving average crossover strategy
std::string tradingStrategy(const std::vector<Stock>& prices) {
    // Calculate the moving average over the last 5 prices
    double sum = 0.0;
    for (size_t i = prices.size() > 5 ? prices.size() - 5 : 0; i < prices.size(); ++i) {
        sum += prices[i].price;
    }
    double movingAverage = sum / std::min(static_cast<size_t>(prices.size()), static_cast<size_t>(5));


    //reducedBranching();
    branching();

    // constexpr int kSize = 10000000;  
    // std::vector<int> data(kSize);
    // std::vector<int> indices(kSize);
    // for(auto& index : indices) {
    //     index = rand() % kSize;
    // }
  
    // int sumCold = 0;
    //     // Access data in random order
    // for (int i = 0; i < kSize; ++i) {
    //   sumCold += data[indices[i]];
    // }

    // int sum_warm = 0;
    // for (int i = 0; i < kSize; ++i) {
    //   sum_warm += data[i];
    // }
   
 
    // // Run the benchmark
    // int sumWarm = 0;
    // // Access data in sequential order again
    // for (int i = 0; i < kSize; ++i) {
    //     sumWarm += data[i];
    // }
 
  
    // int unrolling = 0;
    // for(int i = 0; i < 10000000; i+=4)
    // {
    //     unrolling += 4;
    // }
    // unrolling = 0;
    // for(int i = 0; i < 10000000; i+=4)
    // {
    //     unrolling += 4;
    // }
    // unrolling = 0;
    // for(int i = 0; i < 10000000; i+=4)
    // {
    //     unrolling += 4;
    // }
    // unrolling = 0;
    // for(int i = 0; i < 10000000; i+=4)
    // {
    //     unrolling += 4;
    // }
    // unrolling = 0;
    // for(int i = 0; i < 10000000; i+=4)
    // {
    //     unrolling += 4;
    // }

    // Determine the current price trend based on the last price and the moving average
    double lastPrice = prices.back().price;
    if (lastPrice > movingAverage) {
        return "Buy";
    } else if (lastPrice < movingAverage) {
        return "Sell";
    } else {
        return "Hold";
    }
};

int main() {

    // timing 
    auto start = std::chrono::high_resolution_clock::now();

    {
        std::vector<Stock> stockPrices = generateStockPrices();

        // Print out the generated stock prices
        for (const auto& stock : stockPrices) {
            std::cout << "Stock: " << stock.name << ", Price: $" << stock.price << std::endl;
        }
        cout << tradingStrategy(stockPrices) << "\n";
        stockPrices = generateStockPrices();
        cout << tradingStrategy(stockPrices) << "\n";

    }

    {
        std::vector<CountryLatency> latencies = generateLatencies();

        // Print out the generated network latency values
        for (const auto& latency : latencies) {
            std::cout << "Country: " << latency.country << ", Latency: " << latency.latency << " ms" << std::endl;
        }
    }

    // end of timing
    {
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start;
        std::cout << "Elapsed time: " << elapsed.count() << " seconds" << std::endl;
    }


    return 0;
}

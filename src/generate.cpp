#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <ctime>
#include <string>
#include <cmath>
#include "Stock.h"

using namespace std;

std::string getTimestamp() {
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);

    std::stringstream stream;
    stream << std::put_time(std::localtime(&time), "%Y-%m-%d %H:%M:%S %Z");
    return stream.str();
}

vector<string> generateTickerNames(int size) {
    vector<string> tickers;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(65, 90);
    uniform_int_distribution<> lengthDist(3, 5);

    for (int i = 0; i < size; ++i) {
        string ticker;
        for (int j = 0; j < lengthDist(gen); ++j) ticker += char(dist(gen));
        tickers.push_back(ticker);
    }
    return tickers;
}

std::vector<Stock> generateStocks(const std::vector<std::string>& tickers) {
    std::vector<Stock> stocks;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> priceDist(0.10, 900.0);
    std::uniform_real_distribution<> changePercentageDist(0.01, 1000.0);
    std::uniform_int_distribution<> volumeDist(1000, 1000000);

    for (const auto& ticker : tickers) {
        double price = priceDist(gen);
        double changePercentage = changePercentageDist(gen);
        double changeAmount = (changePercentage / 100) * price;
        stocks.emplace_back(ticker, price, changeAmount, changePercentage, volumeDist(gen));
    }
    return stocks;
}

void writeJSON(const vector<Stock>& stocks, const string& filename) {
    ofstream file(filename);
    file << "{\n";
    file << "\t\"metadata\": \"Top gainers, losers, and most actively traded US tickers\",\n";
    file << "\t\"last_updated\": \"" << getTimestamp() << "\",\n";
    file << "\t\"top_gainers\": [\n";

    for (int i = 0; i < 30000; i++) {
        const auto& s = stocks[i];
        file << "\t\t{\"ticker\": \"" << s.ticker
                << "\", \"price\": \"" << s.price
                << "\", \"change_amount\": \"" << s.changeAmount
                << "\", \"change_percentage\": \"" << s.changePercentage << "%"
                << "\", \"volume\": \"" << s.volume << "\"}";
        if (i != 29999) file << ",";
        file << "\n";
    }
    file << "\t],\n";

    file << "\t\"top_losers\": [\n";
    for (int i = 30000; i < 60000; i++) {
        const auto& s = stocks[i];
        file << "\t\t{\"ticker\": \"" << s.ticker
                << "\", \"price\": \"" << s.price
                << "\", \"change_amount\": \"" << -s.changeAmount
                << "\", \"change_percentage\": \"-" << s.changePercentage << "%"
                << "\", \"volume\": \"" << s.volume << "\"}";
        if (i != 59999) file << ",";
        file << "\n";
    }
    file << "\t],\n";

    file << "\t\"most_actively_traded\": [\n";
    for (int i = 60000; i < 100000; i++) {
        const auto& s = stocks[i];
        double changeSign = i % 2 == 0 ? 1 : -1;
        file << "\t\t{\"ticker\": \"" << s.ticker
                << "\", \"price\": \"" << s.price
                << "\", \"change_amount\": \"" << changeSign * s.changeAmount
                << "\", \"change_percentage\": \"" << (changeSign > 0 ? "" : "-") << s.changePercentage << "%"
                << "\", \"volume\": \"" << s.volume << "\"}";
        if (i != 99999) file << ",";
        file << "\n";
    }
    file << "\t]\n";
    file << "}\n";
    file.close();
}

int main() {
    vector<string> tickers = generateTickerNames(100000);
    vector<Stock> stocks = generateStocks(tickers);
    writeJSON(stocks, "../stock_data.json");
    cout << "Successfully generated " << stocks.size() << " entries." << endl;
    return 0;
}

#pragma once
#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include "Stock.h"
#include "AlphaVantageAPI.h"

using namespace std;

class StockProcessor {
private:
    AlphaVantageAPI::function function;
public:
    StockProcessor(AlphaVantageAPI::function function) : function(function) {}

    std::priority_queue<Stock> maxHeap;
    std::unordered_map<std::string, Stock> stockMap;

    void addStock(const std::string& ticker, double price, double change, double changePercentage, double volume) {
        Stock stock(ticker, price, change, changePercentage, volume, function);
        stockMap.emplace(ticker, stock);
        maxHeap.push(stock);
    }

    vector<Stock> getHeap() {
        vector<Stock> result;
        auto tempHeap = maxHeap;
        while (!tempHeap.empty()) {
            Stock topStock = tempHeap.top();
            tempHeap.pop();
            result.push_back(topStock);
        }
        return result;
    }

    void clearHeap() {
        while (!maxHeap.empty()) maxHeap.pop();
        stockMap.clear();
    }
};

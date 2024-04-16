#pragma once
#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include "StockData.h"

class StockMarketVisualizer {
private:
    std::vector<Stock> heap;
    std::unordered_map<std::string, size_t> stockIndices;

    void heapifyUp(size_t index) {
        while (index > 0) {
            size_t parentIndex = (index - 1) / 2;
            if (heap[index] < heap[parentIndex]) {
                std::swap(heap[index], heap[parentIndex]);
                stockIndices[heap[index].ticker] = index;
                index = parentIndex;
            } else {
                break;
            }
        }
        stockIndices[heap[index].ticker] = index;
    }

    void heapifyDown(size_t index, size_t size) {
        size_t left = 2 * index + 1;
        size_t right = 2 * index + 2;
        size_t largest = index;

        if (left < size && heap[left] < heap[largest]) largest = left;
        if (right < size && heap[right] < heap[largest]) largest = right;

        if (largest != index) {
            std::swap(heap[index], heap[largest]);
            stockIndices[heap[index].ticker] = index;
            stockIndices[heap[largest].ticker] = largest;
            heapifyDown(largest, size);
        }
    }


public:
    void addStock(const std::string& ticker, double volatility, double price, int volume) {
        Stock stock(ticker, volatility, price, volume);
        heap.push_back(stock);
        size_t index = heap.size() - 1;
        stockIndices[ticker] = index;
        heapifyUp(index);
    }

    void updateStock(const std::string& ticker, double newPrice, int newVolume) {
        if (stockIndices.find(ticker) != stockIndices.end()) {
            size_t index = stockIndices[ticker];
            heap[index].price = newPrice;
            heap[index].volume = newVolume;

            if (newPrice > heap[index].price) {
                heapifyUp(index);
            } else {
                heapifyDown(index, heap.size());
            }
        }
    }

    void displayStocks() {
        for (const auto& stock : heap) {
            std::cout << "Ticker: " << stock.ticker
                      << ", Volatility: " << stock.volatility
                      << ", Price: " << stock.price
                      << ", Volume: " << stock.volume << std::endl;
        }
    }
};
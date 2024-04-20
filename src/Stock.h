#pragma once
#include <iostream>
#include <cmath>
#include <sstream>
#include <iomanip>
#include "AlphaVantageAPI.h"

class Stock {
public:
    std::string ticker;
    double price;
    double changeAmount;
    double changePercentage;
    int volume;
    AlphaVantageAPI::function function;

    Stock(std::string ticker, double price, double changeAmount, double changePercentage, double volume, AlphaVantageAPI::function function) : 
        ticker(ticker), price(price), changeAmount(changeAmount), changePercentage(changePercentage), volume(volume), function(function) {}

    Stock(std::string ticker, double price, double changeAmount, double changePercentage, double volume) : 
        ticker(ticker), price(price), changeAmount(changeAmount), changePercentage(changePercentage), volume(volume) {}

    std::string getChangePercentage() const {
        std::stringstream stream;
        stream << std::fixed << std::setprecision(2) << changePercentage;
        return stream.str();
    }

    bool operator<(const Stock& other) const {
        return function != AlphaVantageAPI::function::MOST_ACTIVELY_TRADED ? 
        (abs(changePercentage) < abs(other.changePercentage)) : 
        (volume < other.volume);
    }
};
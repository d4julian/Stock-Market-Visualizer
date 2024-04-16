#pragma once
#include <iostream>

class Stock {
public:
    std::string ticker;
    double volatility;
    double price;
    int volume;

    Stock(std::string t, double vol, double pr, int volm) : ticker(t), volatility(vol), price(pr), volume(volm) {}

    bool operator<(const Stock& other) const {
        return volatility < other.volatility;
    }
};
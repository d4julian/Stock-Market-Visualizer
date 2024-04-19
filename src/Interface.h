#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Stock.h"

using namespace std;

class Interface {
public:
    static int displayMenu() {
        int choice = 0;
        cout << endl << "****************************" << endl;
        cout << "Stock Market Visualizer" << endl;
        cout << "****************************" << endl;
        cout << "Please select one of the following options:" << endl;
        cout << "1. Top Gainers (Daily)" << endl;
        cout << "2. Top Losers (Daily)" << endl;
        cout << "3. Most Actively Traded (Daily)" << endl;
        cout << "4. Exit" << endl;
        cout << "****************************" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        return choice;
    }

    static void displayStocks(const AlphaVantageAPI::function function, const vector<Stock>& stocks) {
        string title;
        switch (function) {
            default:
            case AlphaVantageAPI::function::TOP_GAINERS: title = "Top Gainers"; break;
            case AlphaVantageAPI::function::TOP_LOSERS: title = "Top Losers"; break;
            case AlphaVantageAPI::function::MOST_ACTIVELY_TRADED: title = "Most Actively Traded"; break;
        }
        
        cout << "****************************" << endl;
        cout << title << " (Top 20)" << endl;
        cout << "****************************" << endl;
        for (unsigned int i = 0; i < 20; i++) {
            cout << (i + 1) << ". " << stocks[i].ticker << " | " << 
            (function != AlphaVantageAPI::function::MOST_ACTIVELY_TRADED 
                ? stocks[i].getChangePercentage() + "%": to_string(stocks[i].volume))
            << "" <<  endl;
        }
        cout << "21. Exit" << endl;
    }
    static int displayTickerMenu(const vector<Stock>& stocks) {
        cout << "Please select a ticker (1-20):" << endl;
        int choice = 0;
        cin >> choice;
        if (choice == 21) exit(0);
        while (choice < 1 || choice > 21) {
            cout << "Invalid Choice" << endl;
            continue;
        }

        return choice - 1;
    }

    static void displayDetailedStock(const Stock& stock) {
        cout << endl << "****************************" << endl;
        cout << "Ticker: " << stock.ticker << endl;
        cout << "****************************" << endl;
        cout << "Price: $" << stock.price << endl;
        cout << "Change Amount: $" << stock.changeAmount << endl;
        cout << "Change Percentage: " << stock.getChangePercentage() << "%" << endl;
        cout << "Volume: " << stock.volume << endl;
        cout << endl;
        cout << "Enter anything to return to the main menu" << endl;
        string temp;
        cin >> temp;
    }
};

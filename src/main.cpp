#include <iostream>
#include "AlphaVantageAPI.h"
#include "Interface.h"
#include "Stock.h"
#include "StockProcessor.h"
#include "../json.hpp"

using json = nlohmann::json;
using namespace std;

int main() {
    string input, data;
    AlphaVantageAPI api("../apikey.txt");

    cout << "Would you like to use a sample dataset or data from last market close? (sample/real)" << endl;
    cin >> input;
    if (input == "real") data = api.fetchData();
    else {
        if (input != "sample") cout << "Invalid selection, using sample data..." << endl;
        data = api.readFile("../stock_data.json");
    }

    auto jsonData = json::parse(data);

    int choice;
    while ((choice = Interface::displayMenu()) != 4) {
        try {
            AlphaVantageAPI::function function;
            switch (choice) {
                case 1: function = AlphaVantageAPI::function::TOP_GAINERS; break;
                case 2: function = AlphaVantageAPI::function::TOP_LOSERS; break;
                case 3: function = AlphaVantageAPI::function::MOST_ACTIVELY_TRADED; break;
                default: cout << "Invalid choice. Please try again." << endl; continue;
            }
            StockProcessor processor(function);
            for (const auto& item : jsonData[AlphaVantageAPI::getFunctionName(function)]) {
                string changePercentage = item["change_percentage"].get<string>();
                changePercentage.pop_back();
                processor.addStock(
                    item["ticker"].get<string>(), 
                    stod(item["price"].get<string>()), 
                    stod(item["change_amount"].get<string>()), 
                    stod(changePercentage), 
                    stod(item["volume"].get<string>()));
            }
            
            vector<Stock> stocks = processor.getHeap();
            Interface::displayStocks(function, stocks);
            int index = Interface::displayTickerMenu(stocks);
            Interface::displayDetailedStock(stocks[index]);
            processor.clearHeap();

        } catch (const json::parse_error& e) {
            cerr << "JSON parse error: " << e.what() << endl;
        } catch (const exception& e) {
            cerr << "An error occurred: " << e.what() << endl;
        }
    }

    return 0;
}

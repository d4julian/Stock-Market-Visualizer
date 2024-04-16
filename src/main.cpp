#include <iostream>
#include "AlphaVantageAPI.h"
#include "../json.hpp"

using json = nlohmann::json;
using namespace std;

int main() {
    AlphaVantageAPI api("../apikey.txt");

    try {
        string data = api.fetchData(AlphaVantageAPI::function::TOP_GAINERS_LOSERS);
        auto jsonData = json::parse(data);

        cout << "Top Gainers, Losers, and Most Actively Traded Stocks:" << endl;
        cout << "Metadata: " << jsonData["metadata"] << endl;
        cout << "Last Updated: " << jsonData["last_updated"] << endl;

        if (jsonData.contains("top_gainers")) {
            cout << "\nTop Gainers:\n";
            for (const auto& item : jsonData["top_gainers"]) {
                cout << "Ticker: " << item["ticker"]
                     << ", Price: " << item["price"]
                     << ", Change Amount: " << item["change_amount"]
                     << ", Change Percentage: " << item["change_percentage"]
                     << ", Volume: " << item["volume"] << endl;
            }
        }

        if (jsonData.contains("top_losers")) {
            cout << "\nTop Losers:\n";
            for (const auto& item : jsonData["top_losers"]) {
                cout << "Ticker: " << item["ticker"]
                     << ", Price: " << item["price"]
                     << ", Change Amount: " << item["change_amount"]
                     << ", Change Percentage: " << item["change_percentage"]
                     << ", Volume: " << item["volume"] << endl;
            }
        }

        if (jsonData.contains("most_actively_traded")) {
            cout << "\nMost Actively Traded:\n";
            for (const auto& item : jsonData["most_actively_traded"]) {
                cout << "Ticker: " << item["ticker"]
                     << ", Price: " << item["price"]
                     << ", Change Amount: " << item["change_amount"]
                     << ", Change Percentage: " << item["change_percentage"]
                     << ", Volume: " << item["volume"] << endl;
            }
        }

    } catch (const json::parse_error& e) {
        cerr << "JSON parse error: " << e.what() << endl;
    } catch (const exception& e) {
        cerr << "An error occurred: " << e.what() << endl;
    }

    return 0;
}

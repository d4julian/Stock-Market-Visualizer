#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <curl/curl.h>

class AlphaVantageAPI {
private:
    std::string apiKey;
    static unsigned int WriteCallback(void* contents, unsigned int size, unsigned int nmemb, std::string* userp) {
        userp->append((char*)contents, size * nmemb);
        return size * nmemb;
    }

public:
    AlphaVantageAPI(const std::string& fileName) {
        apiKey = getApiKey(fileName);
    }

    enum function { TIME_SERIES_INTRADAY, TIME_SERIES_DAILY, TIME_SERIES_WEEKLY, TIME_SERIES_WEEKLY_ADJUSTED, TIME_SERIES_MONTHLY, TIME_SERIES_MONTHLY_ADJUSTED, GLOBAL_QUOTE, SYMBOL_SEARCH, MARKET_STATUS, NEWS_SENTIMENT, TOP_GAINERS_LOSERS, OVERVIEW, STOCH, RSI, SIZE };
    const std::string functionNames[SIZE] = {
        "TIME_SERIES_INTRADAY",
        "TIME_SERIES_DAILY",
        "TIME_SERIES_WEEKLY",
        "TIME_SERIES_WEEKLY_ADJUSTED",
        "TIME_SERIES_MONTHLY",
        "TIME_SERIES_MONTHLY_ADJUSTED",
        "GLOBAL_QUOTE",
        "SYMBOL_SEARCH",
        "MARKET_STATUS",
        "NEWS_SENTIMENT",
        "TOP_GAINERS_LOSERS",
        "OVERVIEW",
        "STOCH",
        "RSI"
    };

    std::string fetchData(const function& f) {
        CURL* curl;
        CURLcode res;
        std::string readBuffer;
        //std::string url = "https://www.alphavantage.co/query?function=" + functionNames[f] + "&symbol=" + symbol + "&interval=" + interval + "&apikey=" + apiKey;
        std::string url = "https://www.alphavantage.co/query?function=" + functionNames[f] + "&apikey=" + apiKey;
        std::cout << "URL: " << url << std::endl;

        curl = curl_easy_init();
        if(curl) {
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
            res = curl_easy_perform(curl);
            curl_easy_cleanup(curl);

            if(res != CURLE_OK) {
                std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
                return "";
            }
        }
        return readBuffer;
    }

    std::string getApiKey(const std::string& filename) {
        std::ifstream file(filename);
        std::string apiKey;
        if (file.is_open()) {
            std::getline(file, apiKey);
            file.close();
        } else {
            std::cerr << "Unable to open API key file: " << filename << std::endl;
            exit(0);
        }
        return apiKey;
    }
};
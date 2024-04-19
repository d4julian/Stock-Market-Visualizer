#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <curl/curl.h>

class AlphaVantageAPI {
private:
    std::string apiKey;
    static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
        ((std::string*)userp)->append((char*)contents, size * nmemb);
        return size * nmemb;
    }

public:
    AlphaVantageAPI(const std::string& fileName) {
        apiKey = getApiKey(fileName);
    }

    enum function { TOP_GAINERS_LOSERS, TOP_GAINERS, TOP_LOSERS, MOST_ACTIVELY_TRADED };
    static std::string getFunctionName(const int& index) {
        switch (index) {
            default:
            case 0:
                return "TOP_GAINERS_LOSERS";
            case 1:
                return "top_gainers";
            case 2:
                return "top_losers";
            case 3:
                return "most_actively_traded";
        }
    }

    std::string fetchData() {
        if (apiKey.empty()) {
            std::cout << "Please generate an API key on the Alpha Vantage website!" << 
            std::endl << "https://www.alphavantage.co/support/#api-key" << std::endl;
            exit(0);
        }
        CURL* curl;
        CURLcode res;
        std::string readBuffer;
        std::string url = "https://www.alphavantage.co/query?function=" + getFunctionName(TOP_GAINERS_LOSERS) + "&apikey=" + apiKey;
        std::cout << "URL: " << url << std::endl;

        curl = curl_easy_init();
        if (curl) {
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
            res = curl_easy_perform(curl);
            curl_easy_cleanup(curl);

            if(res != CURLE_OK) {
                std::cerr << "Could not fetch from URL: " << curl_easy_strerror(res) << std::endl;
                exit (0);
            }
        }
        return readBuffer;
    }
    
    std::string readFile(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Failed to open file: " << filename << std::endl;
            exit (0);
        }

        std::stringstream buffer;
        buffer << file.rdbuf();
        file.close();
        return buffer.str();
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
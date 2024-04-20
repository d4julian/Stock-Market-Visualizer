# Stock Market Visualizer

## Project Overview
The Stock Market Visualizer is designed to provide a dynamic view of stock market trends, focusing on top gainers, top losers, and most actively traded stocks. This data could be very useful for stock and option traders that are looking for specific stocks that meet a certain criteria. Utilizing live data from the [Alpha Vantage API](https://www.alphavantage.co/documentation/), this tool aids traders in making informed decisions.

## Features
- **Live Data:** Fetch and display real stock market data (from last trading day close).
- **Sample Data:** Generate 100,000 stocks to use as sample data.
- **Stock Categories:** View top gainers, top losers, and most actively traded stocks.
- **Detailed Stock Data:** Show detailed stock data for a certain stock, such as: price, change, change percentage, and volume.
- **User-Friendly Interface:** Easy to use and user-friendly interface.

## Technologies Used
- C++
- [libCURL](https://github.com/curl/curl?tab=readme-ov-file) for API communication
- JSON for data manipulation, specifically using the [JSON for Modern C++](https://github.com/nlohmann/json) library by Niels Lohmann
- [Alpha Vantage API](https://www.alphavantage.co/documentation/) for live stock trading data

## Using the Alpha Vantage API
If you would like to use the Alpha Vantage API instead of the sample data, you will need to sign up for a unique API key.
1. **Claiming your free API Key**
- You can generate your free API Key on the [Alpha Vantage API website](https://www.alphavantage.co/support/#api-key)
2. **Implementing your key into the program**
- Once you have your key, paste it into the apikey.txt file and you can now utilize live data;

## Running the program
1. **Clone the repository:**
   ```bash
   git clone https://github.com/yourusername/Stock-Market-Visualizer.git
2. **Navigate to the project directory**
   ```bash
   cd Stock-Market-Visualizer
3. **Verify you have cURL installed**
   ```bash
   curl --version
If it is not installed, here is a good resource that you can use to install it: 

https://help.ubidots.com/en/articles/2165289-learn-how-to-install-run-curl-on-windows-macosx-linux (Open at your own discretion)

4. **Compile the source code using g++**

MacOS:
   ```bash
   g++ -std=c++17 main.cpp -o main -lcurl
   ```
Windows:
   ```bash
   g++ -std=c++17 -I<path_to_curl_include_dir> main.cpp -o main -L<path_to_curl_lib_dir> -lcurl
   ```
5. **Run the application**

MacOS:
   ```bash
   ./main
   ```
Windows:
   ```bash
   main
   ```
## Generating sample data
This program allows for 100,000 stocks to be generated to use as sample data. To generate the sample data stored in stock_data.json use the following steps:
1. **Compile the source code using g++**

MacOS:
   ```bash
   g++ -std=c++17 generate.cpp -o generate -lcurl
   ```
Windows:
   ```bash
   g++ -std=c++17 -I<path_to_curl_include_dir> generate.cpp -o generate -L<path_to_curl_lib_dir> -lcurl
   ```
5. **Run the application**

MacOS:
   ```bash
   ./generate
   ```

Windows:
   ```bash
   generate
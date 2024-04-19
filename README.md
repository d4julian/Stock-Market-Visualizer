# Stock Market Visualizer

## Project Overview
The Stock Market Visualizer is designed to provide a dynamic view of stock market trends, focusing on top gainers, top losers, and most actively traded stocks. This data could be very useful for stock and option traders that are looking for specific stocks that meet a certain criteria. Utilizing real-time data from the [Alpha Vantage API](https://www.alphavantage.co/documentation/), this tool aids traders in making informed decisions.

## Features
- **Real-Time Data:** Fetch and display real-time stock market data.
- **Sample Data:** Generate 100,000 stocks to use as sample data.
- **Stock Categories:** View top gainers, top losers, and most actively traded stocks.
- **Detailed Stock Data:** Show detailed stock data for a certain stock, such as: price, change, change percentage, and volume.
- **User-Friendly Interface:** Easy to use and user-friendly interface.

## Technologies Used
- C++
- [libCURL](https://github.com/curl/curl?tab=readme-ov-file) for API communication
- JSON for data manipulation, specifically using the [JSON for Modern C++](https://github.com/nlohmann/json) library by Niels Lohmann
- [Alpha Vantage API](https://www.alphavantage.co/documentation/) for live stock trading data

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
   ```bash
   g++ -std=c++17 main.cpp -o main -lcurl
5. **Run the application**
   ```bash
   ./main
## Generating sample data
This program allows for 100,000 stocks to be generated to use as sample data. To generate the sample data stored in stock_data.json use the following steps:
1. **Compile the source code using g++**
   ```bash
   g++ -std=c++17 generate.cpp -o generate
5. **Run the application**
   ```bash
   ./generate
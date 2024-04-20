from app import app
from dataFetch import *
from database.database import insertOptions, queryOptions
from HashTable import HashTable


def setup_environment():
    print("Setting up the environment...")
    tickers = get_sp500_tickers()  # get tickers
    options_data = getOptionsData(tickers)  # get stock options data from all tickers and dates up to 100,000 points
    insertOptions(options_data)  # store them in SQL database table


def compute_Statistics():
    print("Computing statistics...")
    options_data = queryOptions() # get data from database
    ht = HashTable()
    for option in options_data:
        ht.insert(option['ticker'], option)
    stats = ht.calculate_stats()
    return stats


def start_server():
    print("Starting server...")
    app.stats = compute_Statistics() # store stats in app
    app.run(debug=True)


if __name__ == '__main__':
    setup_environment()
    start_server()
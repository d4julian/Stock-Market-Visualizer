"""
Gets options data using external APIs.
Includes setup for rate limiting and caching.
Keeps API-specific stuff separate from other parts of the application
"""
import yfinance as yf
import pandas as pd
from requests import Session
from requests_cache import CacheMixin, SQLiteCache
from requests_ratelimiter import LimiterMixin, MemoryQueueBucket
from pyrate_limiter import Duration, RequestRate, Limiter


# this is to set up rate limiting and caching for API call spam prevention
class CachedLimiterSession(CacheMixin, LimiterMixin, Session):
    pass


# need to get the tickers for the SP500 index = 503 tickers total
def get_sp500_tickers():
    sp500_table = pd.read_html("https://en.wikipedia.org/wiki/List_of_S%26P_500_companies")
    sp500 = sp500_table[0]
    return sp500["Symbol"].tolist()


def getOptionsData(tickers):
    # this is to set up rate limiting and caching for API call spam prevention
    session = CachedLimiterSession(
        limiter=Limiter(RequestRate(10, Duration.SECOND * 2)),  # max 2 requests per 5 seconds
        bucket_class=MemoryQueueBucket,
        backend=SQLiteCache("yfinance.cache"),
    )
    # now get options data
    options_data = []   # initialize list
    for ticker in tickers:  # loop over all stock tickers
        stock = yf.Ticker(ticker, session=session)  # get ticker data
        exp_dates = stock.options   # get available expiration dates for that ticker
        for date in exp_dates:  # loops over every available options date for the ticker
            opt = stock.option_chain(date) # grabs the option chain for current ticker and date in form of a data frame
            calls = opt.calls.to_dict("records") # convert the dataframe into a list of dictionaries
            for call in calls:
                call.update(
                    {
                        'ticker': ticker,
                        'expiration': date,
                        'option_type': 'call'
                    })
            options_data.extend(calls)
            puts = opt.puts.to_dict("records")
            for put in puts:
                put.update(
                    {
                        'ticker': ticker,
                        'expiration': date,
                        'option_type': 'put'
                    })
            options_data.extend(puts)
            if len(options_data) >= 100000:
                return options_data[:100000]    # only return first 100,000 data values
   # for option in options_data:
    #    if not isinstance(option, dict):
    #        print(f"Invalid data type detected: {type(option)} - {option}")
    return options_data
# example output list of dictionaries: options_data
# [{'contractSymbol': 'AAPL220624C00145000', 'strike': 145.0, 'expiration': '2022-06-24', 'type': 'call'},
# {'contractSymbol': 'AAPL220624P00145000', 'strike': 145.0, 'expiration': '2022-06-24', 'type': 'put'}]

"""
 #TESTING
# Define the ticker symbol of the underlying asset
ticker_symbol = 'MO'

# Create a Ticker object
aapl = yf.Ticker(ticker_symbol)

# Get the options chain for the ticker
date = aapl.options
opt = aapl.option_chain(date[0])
print(date[0]) # 2024-04-26
# Print the call options
print("Call Options:")
with pd.option_context('display.max_rows', 100, 'display.max_columns', 14):
    # Code here will use the adjusted display settings
    print(opt.calls)

# Print the put options
print("\nPut Options:")
with pd.option_context('display.max_rows', 100, 'display.max_columns', 14):
    print(opt.puts)
#"""
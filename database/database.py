"""
Handle database connection and session management here.
Includes functions to insert data into the database.
Centralizes database operations, improving modularity and reuse.
"""
from sqlalchemy import create_engine
from sqlalchemy.orm import sessionmaker
from database.models import *
from datetime import datetime
import pandas as pd


# Create an SQLite engine and base
engine = create_engine('sqlite:///options.db')
Base.metadata.create_all(engine)
Session = sessionmaker(bind=engine)


def prep_data_for_insert(options_data):
    for option in options_data:
        # Check if the option is a dictionary and has the expected keys
        if isinstance(option, dict) and 'lastTradeDate' in option and 'expiration' in option:
            # Convert 'lastTradeDate' if it is a pd.Timestamp
            if isinstance(option['lastTradeDate'], pd.Timestamp):
                option['lastTradeDate'] = option['lastTradeDate'].strftime('%Y-%m-%d %H:%M:%S')

            # Convert 'expiration' if it is a pd.Timestamp
            if isinstance(option['expiration'], pd.Timestamp):
                option['expiration'] = option['expiration'].strftime('%Y-%m-%d')
        else:
            print(f"Skipping or logging malformed data: {option}")
    return options_data


# Insert options data into database
def insertOptions(options_data):
    session = Session()
    options_data = prep_data_for_insert(options_data)
    for data in options_data:
        option = Option(**data)
        session.add(option)
    session.commit()
    session.close()


def queryOptions():
    session = Session()
    try:
        options = session.query(Option).all()
        result = [
            {
                'ticker': option.ticker,
                'option_type': option.option_type,
                'strike': option.strike,
                'expiration': option.expiration,
                'volume': option.volume,
            }
            for option in options
        ]
        return result
    finally:
        session.close()
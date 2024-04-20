"""
Handle database connection and session management here.
Includes functions to insert data into the database.
Centralizes database operations, improving modularity and reuse.
"""
from sqlalchemy import create_engine
from sqlalchemy.orm import sessionmaker
from database.models import *


# Create an SQLite engine and base
engine = create_engine('sqlite:///options.db')
Base.metadata.create_all(engine)
Session = sessionmaker(bind=engine)


# Insert options data into database
def insertOptions(options_data):
    session = Session()
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
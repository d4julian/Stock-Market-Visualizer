""" 
Define all ORM models here.
This will include the Option class.
Keeps all database schemas in one place -> easy to manage
"""
from sqlalchemy import Column, Integer, String, Float
from sqlalchemy.ext.declarative import declarative_base

Base = declarative_base() # base class connecting ORM models to the database


class Option(Base): # our object model class
    # define the columns and types
    __tablename__ = 'options'
    id = Column(Integer, primary_key=True)
    contractSymbol = Column(String)
    lastTradeDate = Column(String)
    strike = Column(Float)
    lastPrice = Column(Float)
    bid = Column(Float)
    ask = Column(Float)
    change = Column(Float)
    percentChange = Column(Float)
    volume = Column(Float)
    openInterest = Column(Integer)
    impliedVolatility = Column(Float)
    inTheMoney = Column(String)
    contractSize = Column(String)
    currency = Column(String)
    ticker = Column(String)
    expiration = Column(String)
    option_type = Column(String)
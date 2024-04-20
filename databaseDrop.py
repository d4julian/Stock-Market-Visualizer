from sqlalchemy import create_engine
from database.models import Base  # Import your declarative base

engine = create_engine('sqlite:///options.db')

# Drop all tables (careful with this in production)
Base.metadata.drop_all(engine)

# Recreate all tables with the new definitions
Base.metadata.create_all(engine)
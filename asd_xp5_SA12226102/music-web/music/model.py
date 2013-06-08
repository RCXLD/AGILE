from sqlalchemy import Column, Integer, String, ForeignKey, Table
from sqlalchemy.orm import relationship, backref
from database import Base

band_genre_table = Table('association', Base.metadata, Column('band_id', Integer, ForeignKey('band.id')), Column('genre_id', Integer, ForeignKey('genre.id')))

class Band(Base):
  __tablename__ = 'band'
  
  id              = Column(Integer, primary_key = True)
  Name            = Column(String(256))
  FirstYearActive = Column(Integer)
  LastYearActive  = Column(String(256))
  PlaceOfOrigin   = Column(String(256))
  
  Albums          = relationship('Album', backref = 'band')
  Genres          = relationship('Genre', secondary = band_genre_table, backref = 'band')
  
  def __init__(self, name, first_year, last_year, origin):
    self.Name = name
    self.FirstYearActive = first_year
    self.LastYearActive  = last_year
    self.PlaceOfOrigin   = origin
    
class Album(Base):
  __tablename__ = 'album'
  
  id        = Column(Integer, primary_key = True)
  Name      = Column(String(256))
  YearOfPub = Column(Integer)
  Label     = Column(String(256))
  
  BandID    = Column(Integer, ForeignKey('band.id'))
  Tracks   = relationship('Track', backref = 'album')
  
  def __init__(self, name, year, label):
    self.Name = name
    self.YearOfPub = year
    self.Label = label
    
class Track(Base):
  __tablename__ = 'track'
  
  id       = Column(Integer, primary_key = True)
  Name     = Column(String(256))
  Duration = Column(Integer)
  
  Album    = Column(Integer, ForeignKey('album.id')) 
  
  def __init__(self, name, duration):
    self.Name = name
    self.Duration = duration
    
class Genre(Base):
  __tablename__ = 'genre'
  
  id       = Column(Integer, primary_key = True)
  Name     = Column(String(256))
  
  def __init__(self, name):
    self.Name = name

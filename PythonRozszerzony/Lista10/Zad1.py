from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy import Column, Integer, String, ForeignKey
from sqlalchemy import create_engine
from sqlalchemy.orm import sessionmaker, relationship
import sys

Base = declarative_base()

class Song(Base):
    __tablename__ = 'Song'

    id = Column(Integer, primary_key=True)
    author_id = Column(Integer, ForeignKey('bands.id'))
    title = Column(String)
    year = Column(Integer)

    author = relationship("Band", back_populates="songs")

    def __repr__(self):
        return "<Song(title= '%s', author= '%s', year= '%d')>" % (self.title, self.author, self.year)

class Band(Base):
    __tablename__ = 'bands'

    id = Column(Integer, primary_key=True)
    name = Column(String)

    songs = relationship("Song", order_by=Song.id, back_populates="author")

    def __repr__(self):
        return "<Band(name= '%s')>" % (self.name)

def add_song():
    engine = create_engine('sqlite:///books.db')
    Session = sessionmaker(bind=engine)
    session = Session()

    title = sys.argv[3]
    author = sys.argv[4]
    year = sys.argv[5]
    try:
        base_author = session.query(Band).filter_by(name=author).one()
    except:
        print("Author doesn't exist in database")
        return

    new_song = Song(title=title, year=year)
    base_author.songs.append(new_song)
    session.add(new_song)
    session.commit()

def add_band():
    engine = create_engine('sqlite:///books.db')
    Session = sessionmaker(bind=engine)
    session = Session()

    name = sys.argv[3]

    new_band = Band(name=name)
    session.add(new_band)
    session.commit()

if len(sys.argv) == 2 and sys.argv[1] == 'start':
    engine = create_engine('sqlite:///books.db')
    Base.metadata.create_all(engine)

elif (len(sys.argv) == 6 or len(sys.argv) == 4) and sys.argv[1] == 'add':
    if sys.argv[2] == 'song':
        add_song()
    if sys.argv[2] == 'band':
        add_band()

elif len(sys.argv) == 2 and sys.argv[1] == 'show_bands':
    engine = create_engine('sqlite:///books.db')
    Session = sessionmaker(bind=engine)
    session = Session()
    for band in session.query(Band).order_by(Band.id):
        print(band)

elif len(sys.argv) == 2 and sys.argv[1] == 'show_songs':
    engine = create_engine('sqlite:///books.db')
    Session = sessionmaker(bind=engine)
    session = Session()
    for song in session.query(Song).order_by(Song.id):
        print(song)

elif len(sys.argv) == 2 and sys.argv[1] == 'help':
    print("start -- for creating database file")
    print("add (band|song) <data> -- for adding new band or song (e.g add song Something Aerosmith 1997)")
    print("show_bands -- for showing Band table")
    print("show_songs -- for showing Song table")

else:
    print("Wrong input")
    print("Use help for instructions")
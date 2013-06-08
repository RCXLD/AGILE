from sqlalchemy.orm.exc import NoResultFound

import music.database
import music.model

music.database.db_init()

with open('bands.txt', 'r') as f:
  for line in f:
    name = line.split(',')[0]
    first = line.split(',')[1].split('-')[0]
    last = line.split(',')[1].split('-')[-1]
    origin = ("".join(line.split(',')[3:])).rstrip()
    band = music.model.Band(name, int(first), last, origin)
    genre = list(line.split(',')[2].split(';'))
    for ge in genre:
      try:
        gen = music.database.db_session.query(music.model.Genre).filter(music.model.Genre.Name == ge).one()
      except NoResultFound:
        gen = music.model.Genre(ge)
        music.database.db_session.add(gen)
      band.Genres.append(gen)
        
    music.database.db_session.add(band)   
   
with open('albums.txt', 'r') as f:
  line = f.readline()
  while (line != ''):
    print [line]
    name  = line.split(',')[0]
    year  = line.split(',')[1]
    label = line.split(',')[2]
    band_name = line.split(',')[3].rstrip()
    album = music.model.Album(name, year, label)
    line = f.readline()
    while(line.count('-') < 10):
        print [line]
        track_name = line.split(',')[0].rstrip()
        track_duration = int(line.split(',')[1].split(':')[0])*60 + int(line.split(',')[1].split(':')[1])
        track = music.model.Track(track_name, track_duration)
        music.database.db_session.add(track)
        album.Tracks.append(track)
        line = f.readline()
    band = music.database.db_session.query(music.model.Band).filter(music.model.Band.Name == band_name).one()
    music.database.db_session.add(album)
    band.Albums.append(album)
    line = f.readline()
    
    
music.database.db_session.commit()


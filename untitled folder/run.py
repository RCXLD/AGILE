from flask import Flask,render_template,request,g,redirect,url_for
from sqlalchemy.orm.exc import NoResultFound

import music.database
import music.model
app=Flask(__name__)

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/all/bands')
def show_bands():
    bands=music.database.db_session.query(music.model.Band).order_by("Name")
    return render_template('bands.html',bands=bands)
    
@app.route('/all/albums')
def show_albums():
	album=music.database.db_session.query(music.model.Album).order_by("Name")
	return render_template('albums.html',albums=album)
	
@app.route('/albums/<int:album_id>')
def show_album(album_id=None):
	error=None
	try:
		album=music.database.db_session.query(music.model.Album).filter(music.model.Album.id=album_id).one()
	except NoResultFound:
		error="No This album"
	return render_template('album.html',album=album,error=error)
	
@app.route('/bands/<int:band_id>')
def show_band(band_id=None):
	error=None
	try:
		band=music.database.db_session.query(music.model.Band).filter(music.model.Band.id==band_id).one()
	except NoResultFound:
		error="No theis Band"
	return render_template('band.html',band=band,error=error)

@app.route('/create/band',methods=('GET','POST'))
def create_band():
	if request.method=='POST':
		name=request.form['name']
		band=music.model.Band(name,,,)
		music.database.db_session.add(band)
		music.database.db_session.commit()
		return redirect(url_for('show_bands'))
	else:
		return render_template('add_band.html')
		
@app.route('/delete/band/<int:band_id>',methods=('GET','POST'))
def delete_band(band_id=None):
	error=None
	try:
		band=music.database.db_session.query(music.model.Band).filter(music.model.Band.id==band_id).one()
	except NoResultFoud:
		error='No This Band'
		return render_template('delete_band.html',error=error)
	if request.method='POST':
		if error==None:
			music.database.db_session.delete(band)
			music.database.db_session.commit()
			return redirect(url_for('show_bands'))
		else:
			return render_template('delete_band.html',band=band,error=error)

	

    


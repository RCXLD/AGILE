from flask import Flask, flash, g, abort, render_template, session, request, redirect, url_for
app = Flask(__name__)

import os, sqlalchemy

from sqlalchemy import desc

import linky.jinja_filters
from linky.database import db_init, db_session
from linky.model import User, Link


# --- Get all filters from linky.jinja_filters --------------------------------

from inspect import getmembers, isfunction
custom_filters = { name : function for name, function in getmembers(linky.jinja_filters) if isfunction(function)}

app.jinja_env.filters.update(custom_filters)



# --- Common utility functions ------------------------------------------------

def check_user_is_logged():
	# Send 'Unauthorized' if no user logged in
	if g.user is None:
		abort(401)



# --- Flask hooks -------------------------------------------------------------

@app.before_request
def before_request():
	# Ensure we got a user instance if the user is logged in
	g.user = None
	if 'user_id' in session:
		g.user = db_session.query(User).filter(User.id == session['user_id']).one()



@app.teardown_request
def shutdown_session(exception = None):
	db_session.remove()



# --- Controlers --------------------------------------------------------------

@app.route('/')
def index():
	if 'user_id' in session:
		return redirect(url_for('home'))
	else:
		return render_template('index.html')



@app.route('/home')
def home():
	check_user_is_logged()

	links = db_session.query(Link).order_by(desc(Link.date)).all()
	return render_template('home.html', user = g.user, link_list = links)



@app.route('/user/<name>')
def show_user(name):
	check_user_is_logged()

	# Check if the user exists
	try:
		owner = db_session.query(User).filter(User.name == name).one()
	except sqlalchemy.orm.exc.NoResultFound:
		abort(404)		

	# Show the page for that user
	links = db_session.query(Link).filter(Link.user_id == owner.id).order_by(desc(Link.date)).all()
	return render_template('user.html', user = g.user, owner = owner, link_list = links)



@app.route('/post', methods = ('GET', 'POST'))
def post_link():
	check_user_is_logged()

	# POST request
	if request.method == 'POST':
		# Create the link
		link = Link(request.form['url'])
		link.comment = request.form['comment']
		link.user = g.user

		# Update db
		db_session.add(link)
		db_session.commit()
		return redirect(url_for('home'))
	# GET Request
	else:
		return render_template('post.html', user = g.user)	



@app.route('/login', methods = ('GET', 'POST'))
def login():
	# POST request
	if request.method == 'POST':
		# Try to find the user
		try:
			user = db_session.query(User).filter(User.email == request.form['email']).one()
		except sqlalchemy.orm.exc.NoResultFound:
			error = 'This email have not be registered'
			return render_template('login.html', user = g.user, error = error)

		# Check the user password
		if not user.check_password(request.form['password']):
			error = 'Wrong password'
			return render_template('login.html', user = g.user, error = error)

		# Job done
		session['user_id'] = user.id
		return redirect(url_for('home'))
	# GET Request
	else:
		return render_template('login.html', user = g.user)



@app.route('/logout')
def logout():
	session.pop('user_id', None)
	return redirect(url_for('index'))



# --- Entry point -------------------------------------------------------------
	
if __name__ == '__main__':
	app.secret_key = os.urandom(24)
	app.run(debug = True)

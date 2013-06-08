from flask import Flask, flash, g, abort, render_template, session, request, redirect, url_for
app = Flask(__name__)

import os, sqlalchemy

from linky.database import db_init, db_session
from linky.model import User



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
	return render_template('index.html')



@app.route('/home')
def home():
	check_user_is_logged()
	return render_template('home.html', user = g.user)



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

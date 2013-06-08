import os, base64, hashlib

from sqlalchemy import ForeignKey
from sqlalchemy import Column, Integer, Float, String
from sqlalchemy.orm import relationship, backref

from .database import Base



class User(Base):
	__tablename__ = 'user'

	id       = Column(Integer, primary_key = True)
	name     = Column(String(256))
	email    = Column(String(256))
	pwd_hash = Column(String(128))
	pwd_salt = Column(String(48))

	links    = relationship('Link', backref = 'user')

	def __init__(self, name, email):
		self.name  = name
		self.email = email

	def hash_password(self, password, salt):
		return hashlib.sha512(salt + password).hexdigest()

	def set_password(self, password):
		self.pwd_salt = base64.b64encode(os.urandom(32))
		self.pwd_hash = self.hash_password(password, self.pwd_salt)

	def check_password(self, password):
		return self.pwd_hash == self.hash_password(password, self.pwd_salt)

	def __repr__(self):
		return "<User(%d, '%s', %s)>" % (self.id, self.name, self.email)



class Link(Base):
	__tablename__ = 'link'

	id       = Column(Integer, primary_key = True)
	url      = Column(String(1024))
	comment  = Column(String(1024))

	user_id  = Column(Integer, ForeignKey('user.id'))

	def __init__(self, url):
		self.url = url

	def __repr__(self):
		return '<Link<%d>' % self.id

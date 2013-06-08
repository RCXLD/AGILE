import os, os.path, sys, argparse

from linky.database import db_file_name, db_init, db_session
from linky.model import User



def main():
	# Command-line
	parser = argparse.ArgumentParser(description = 'Populate a database from a text file')
	parser.add_argument('input_file', type = argparse.FileType('r'), default = sys.stdin, help = 'a list of users')
	args = parser.parse_args()

	# Delete the db dump if it exists	
	if os.path.exists(db_file_name):
		os.remove(db_file_name)

	#
	# Populate the database
	#
	db_init()

	try:
		for line in args.input_file:
			line = line.strip()
			if len(line) == 0:
				continue

			tokens = line.split()
			user = User(tokens[0], tokens[1])
			user.set_password(tokens[2])
			db_session.add(user)
	except ValueError as e:
		sys.stderr.write('Error while reading "%s"\n' % args.input_file.name)
		sys.stderr.write('%s\n' % e)
		sys.exit(0)

	db_session.commit()



if __name__ == "__main__":
	main()

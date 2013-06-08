import os, os.path, sys, json, argparse

from linky.database import db_file_name, db_init, db_session
from linky.model import User, Link



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
		db_data = json.load(args.input_file)
	except ValueError as e:
		sys.stderr.write('Error while reading "%s"\n' % args.input_file.name)
		sys.stderr.write('%s\n' % e)
		sys.exit(0)

	# Add the users
	for user_data in db_data['users']:
		# Create the user instance
		user = User(user_data['name'], user_data['email'])
		user.set_password(user_data['pwd'])

		# Add each link
		if 'links' in user_data:
			for link_data in user_data['links']:
				link = Link(link_data['url'])
				if 'comment' in link_data:
					link.comment = link_data['comment']
				user.links.append(link)

		# Add the user		
		db_session.add(user)

	# Job done, commiy all
	db_session.commit()



if __name__ == "__main__":
	main()

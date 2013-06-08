import datetime



def datetimeformat(value, format = '%H:%M / %d-%m-%Y'):
	now = datetime.datetime.now()
	time_diff = now - value

	if time_diff.days == 0:
		if time_diff.seconds < 60:
			return '%d seconds ago' % time_diff.seconds
		elif time_diff.seconds < 3600:
			return '%d minutes ago' % (time_diff.seconds / 60)
		else:
			return '%d hours ago' % (time_diff.seconds / 3600)
	elif time_diff.days == 1:
		return 'yesterday'
	elif time_diff.days > 1:
		return '%d days ago' % time_diff.days

	return value.strftime(format)

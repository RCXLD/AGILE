def string2ascii(str2convert):
  return tuple(ord(c) for c in str2convert)

def get_unused_code_list(data):
  return list(set(range(256))-set(string2ascii(data)))

def get_pairs(data):
  return zip(data[:-1],data[1:])
  
def count_pairs(data):
  pairs = get_pairs(data)
  return dict(list((pair, pairs.count(pair)) for pair in pairs))
  
def get_most_frequent_pair(data):
  return max((c,b) for b,c in count_pairs(data).iteritems())

def replace_pair_by_code(data, replace_pair, replace_code):
  return list(c for c in data.replace(replace_pair, replace_code))
  
def compress(data):
  retString = data
  replaceList = []
  while len(retString) > 1:
    replaceList.append((''.join(c for item in get_most_frequent_pair(retString)[1:] for c in item),chr(get_unused_code_list(retString)[-1])))
    retString = ''.join(c for c in replace_pair_by_code(retString, ''.join(c for item in get_most_frequent_pair(retString)[1:] for c in item), chr(get_unused_code_list(retString)[-1])))
  return retString, replaceList

def uncompress(compressed_data, replacement_list):
  result = compressed_data
  for i in range(len(replacement_list)-1,-1,-1):
    result = result.replace(replacement_list[i][1], replacement_list[i][0])
  return result

print "****************************************************"
print "string2ascii('hello')"
print "----------------------------------------------------"  
print string2ascii('hello')

print "****************************************************"
print "get_unused_code_list('hello')"
print "----------------------------------------------------"
print get_unused_code_list('hello')

print "****************************************************"
print "get_pairs('hello')"
print "----------------------------------------------------"
print get_pairs('hello')

print "****************************************************"
print "count_pairs('helllo')"
print "----------------------------------------------------"
print count_pairs('helllo')

print "****************************************************"
print "get_most_frequent_pair('helllo')"
print "----------------------------------------------------"
print get_most_frequent_pair('helllo')

print "****************************************************"
print "replace_pair_by_code('lalalal', 'la', 'X')"
print "----------------------------------------------------"
print replace_pair_by_code('lalalal', 'la', 'X')

print "****************************************************"
print "compress('lalalal')"
print "----------------------------------------------------"
print compress('lalalal')

print "****************************************************"
print "uncompress(*compress('lalalal'))"
print "----------------------------------------------------"
print uncompress(*compress('lalalal'))

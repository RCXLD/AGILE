def TurnAscii(string):
    return tuple(ord(a) for a in string)
        
def get_unused_code_list(data):
    return list(set(range(255))-set(TurnAscii(data)))

def get_pairs(data):
    return zip(data[:-1],data[1:])
    
def count_pairs(data):
    p=get_pairs(data)
    return dict([(c,p.count(c)) for c in set(p)])

def get_most_frequent_pair(data):
    pair_count_map = count_pairs(data)
    return max((count, pair) for pair, count in pair_count_map.iteritems())

def replace_pair_by_code(data,replace_pair,replace_value):
    print replace_value
    return list(c for c in data.replace(replace_pair,str(replace_value)))
        
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
    

string='Hellll World'
print string


from pythonds.basic.stack import Stack

def parChecker(symbolString):
	s= Stack()
	symbol={'{':'}','[':']','(':')'}
	for one in symbolString:
		if one in symbol:
			s.push(one)
		else:
			try:
				tmp = s.pop()
			except IndexError:
				return False
			if symbol[tmp] == one:
				pass
			else:
				return False
	return True

if __name__ == '__main__':
	print(parChecker('{{([][])}}()}'))
	print(parChecker('[{()}]'))
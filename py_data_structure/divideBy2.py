from pythonds.basic.stack import Stack

def divideBy(decNumber,base):
	s = Stack()
	num = '0123456789ABCDEF'
	res = []
	while decNumber:
		s.push(num[decNumber % base])
		decNumber = decNumber // base
	while not s.isEmpty():
		res.append(s.pop()) 
	return res

if __name__ == '__main__':
	print(divideBy(125,2))

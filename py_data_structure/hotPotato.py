from pythonds.basic.queue import Queue

def hotPotato(namelist,num):
	s = Queue()
	for one in namelist:
		s.enqueue(one)

	while s.size() > 1:
		for i in range(num):
			tmp = s.dequeue()
			s.enqueue(tmp)
		tmp = s.dequeue()
	return s.dequeue()
	

if __name__ == '__main__':
	print(hotPotato(["Bill","David","Susan","Jane","Kent","Brad"],6))
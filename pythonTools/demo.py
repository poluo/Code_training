<<<<<<< HEAD
from key import _Getch
import random,os
class game_2048(object):
	"""docstring for  simple 2048 game"""
	def __init__(self):
		self.getchar=_Getch()
		self.arr=[]
		self.scores=0
	def get_num(self):
		num=random.randrange(2,5,2)
		return num
	def game_main(self):
		self.arr=self.get_init_num()
		print('W/UP S/DOWN A/LEFT D/RIGHT')
		self.display(self.arr)
		keys=('w','s','a','d','W','A','S','D')
		#keys=(b'w',b's',b'a',b'd',b'W',b'S',b'A',b'D',b'H',b'P',b'K',b'M')
		try:
			while True:
				c=self.getchar.__call__()
				print(c)
				if c=='q' or c=='Q':
					print('break')
					break
				elif c in keys:
					if c=='w' or c=='W':
						self.arr=self.up_proc(self.arr)
					elif c=='s' or c=='S':
						self.arr=self.down_proc(self.arr)
					if c=='a' or c=='A':
						self.arr=self.left_proc(self.arr)
					if c=='d' or c=='D':
						self.arr=self.right_proc(self.arr)
				elif c=='\xe0':
					pass
				else:
					print('invalid')
			print('Quit the game,you scores',self.scores)
			c=input()
		except KeyboardInterrupt:
			print('Quit the game,you scores',self.scores)
			c=input()
	def get_init_num(self):
		arr=[]
		for i in range(4):
			tmp=[]
			for j in range(4):
				tmp.append(self.get_num())
			arr.append(tmp)
		#print(arr)
		return arr
	def display(self,arr):
		if len(arr)!=4:
			print("invalid array")
			return 1
		for i in arr:
			if len(i)!=4:
				print("invalid array")
				return 1
			else:
				for num in i:
					#print without \n,should get a ','
					#another method sys.stdout.write("Hello World")
					print("   ",num,end=" ")
				print("\n")
	def proc_arr(self,arr):
		count=0
		for element in arr:
			for i in range(3):
				if element[i]==element[i+1]:
					element[i]*=2
					count=count+1
					i=i+1
					while i<=2:
						element[i]=element[i+1]
						i=i+1
					element[i]=self.get_num()
					break
		#display(arr)
		self.scores=self.scores+count
		return arr
	def arr_trans(self,arr):
		re_arr=[]
		for i in range(4):
			tmp=[]
			for j in range(4):
				tmp.append(arr[j][i])
			re_arr.append(tmp)
		#display(re_arr)
		return re_arr
	def proc_arr_rev(self,arr):
		count=0
		for element in arr:
			for i in range(3,0,-1):
				if element[i]==element[i-1]:
					element[i]*=2
					count=count+1
					i=i-1
					while i>=1:
						element[i]=element[i-1]
						i=i-1
					element[i]=self.get_num()
					break
		self.scores=self.scores+1
		return arr
	def up_proc(self,arr):
		arr=self.arr_trans(arr)
		arr=self.proc_arr(arr)
		arr=self.arr_trans(arr)
		os.system('clear') 
		self.display(arr)
		return arr

	def down_proc(self,arr):
		arr=self.arr_trans(arr)
		arr=self.proc_arr_rev(arr)
		arr=self.arr_trans(arr)
		os.system('clear') 
		self.display(arr)
		return arr
	def left_proc(self,arr):
		self.proc_arr(arr)
		os.system('clear') 
		self.display(arr)
		return arr
	def right_proc(self,arr):
		self.proc_arr_rev(arr)
		os.system('clear') 
		self.display(arr)
		return arr


if __name__=="__main__":
	mygame=game_2048()
	mygame.game_main()  
		
=======
import random,sys
def get_num():
	"'retrurn 2 or 4'"
	return random.randrange(2,5,2)
def get_init_num():
	arr=[]
	for i in range(4):
		tmp=[]
		for j in range(4):
			tmp.append(get_num())
		arr.append(tmp)
	#print(arr)
	return arr
def display(arr):
	if len(arr)!=4:
		print("invalid array")
		return 1
	for i in arr:
		if len(i)!=4:
			print("invalid array")
			return 1
		else:
			for num in i:
				#print without \n,should get a ','
				#another method sys.stdout.write("Hello World")
				print("   ",num,end=" ")
			print("\n")
def proc_arr(arr):
	for element in arr:
		for i in range(3):
			if element[i]==element[i+1]:
				element[i]*=2
				i=i+1
				while i<=2:
					element[i]=element[i+1]
					i=i+1
				element[i]=get_num()
				break
	#display(arr)
	return arr
def arr_trans(arr):
	re_arr=[]
	for i in range(4):
		tmp=[]
		for j in range(4):
			tmp.append(arr[j][i])
		re_arr.append(tmp)
	#display(re_arr)
	return re_arr
def proc_arr_rev(arr):
	for element in arr:
		for i in range(3,0,-1):
			if element[i]==element[i-1]:
				element[i]*=2
				i=i-1
				while i>=1:
					element[i]=element[i-1]
					i=i-1
				element[i]=get_num()
				break
	return arr
def up_proc(arr):
	arr=arr_trans(arr)
	arr=proc_arr(arr)
	arr=arr_trans(arr)
	display(arr)

def down_proc(arr):
	arr=arr_trans(arr)
	arr=proc_arr_rev(arr)
	arr=arr_trans(arr)
	display(arr)
def left_proc(arr):
	proc_arr(arr)
	display(arr)
def right_proc(arr):
	proc_arr_rev(arr)
	display(arr)
if __name__=="__main__":
	arr=get_init_num()
	print('------------'*2)
	display(arr)
	print('------------'*2)
	right_proc(arr)
	#arr=arr_rev(arr)
	c=input()
>>>>>>> 51d3708b7ad532ec7596051446b6fe46879a2775

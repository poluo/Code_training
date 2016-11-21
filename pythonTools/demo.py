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

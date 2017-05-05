def count_word(file_name):
    data = {}
    with open(file_name,'r') as fobj:
        for line in fobj:
            word_list = line.split(' ')
            for one in word_list:
                one = one.strip()
                if one in data:
                    data[one] +=1
                else:
                    data[one] = 1
    print(data)
if __name__ == '__main__':
    count_word('./test.txt')

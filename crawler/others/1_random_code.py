import random
import string

CODE_LEN = 15
def gen_code():
    code=''.join(random.sample(string.ascii_letters+string.digits,CODE_LEN))
    return code
if __name__ == '__main__':
    for i in range(10):
        print(gen_code())


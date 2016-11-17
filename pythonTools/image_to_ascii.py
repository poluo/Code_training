import pygame,os,Image
class photo_to_txt():
    def __init__(self,WIDTH=100,HEIGHT=80):
        self.txt=""
        self.width=WIDTH
        self.height=HEIGHT
        self.ascii_char = list("$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\|()1{}[]?-_+~<>i!lI;:,\"^`'. ")
    def get_char(self,r):
        alpha=r[3] if len(r)==4 else 255
        if alpha == 0:  
            return ' '  
        r,g,b=r[0],r[1],r[2]
        length = len(self.ascii_char)  
        gray = int(0.2126 * r + 0.7152 * g + 0.0722 * b)  
        unit = (256.0 + 1)/length  
        return self.ascii_char[int(gray/unit)]
    def transfer(self,input_file):
        photo=Image.open(input_file)
        photo=photo.resize((self.width,self.height),Image.NEAREST)
        for i in range(0,self.height,2):
            for j in range(0,self.width,2):
                r=photo.getpixel((j,i))
                self.txt+=self.get_char(r)
            self.txt+='\n'
    def print_txt(self):
        print(self.txt)
    def out_file(self,out):
        with open(out,'w') as f:
            f.write(self.txt)
    def str_to_photo(self,txt,des):
        pygame.init()
        #字体需要更换，大小需要更改
        font = pygame.font.Font(os.path.join("fonts", "l.TTF"), 24)
        rtext = font.render(txt, True, (0, 0, 0), (255, 255, 255))
        pygame.image.save(rtext, des)
if __name__=='__main__':
    photo=photo_to_txt(100,60)
    photo.str_to_photo('hello,com','test.png')
    photo.transfer('./test.png')
    photo.out_file('./test.txt')

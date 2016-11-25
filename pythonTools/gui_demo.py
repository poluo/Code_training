from tkinter import *
import tkinter.messagebox as messagebox
class gui(Frame):
    """docstring for gui"""
    def __init__(self, arg=None):
        Frame.__init__(self,arg)
        self.pack()
        self.createWidgets()
    def createWidgets(self):
        self.input=Entry(self)
        self.input.pack()
        self.helloLabel=Label(self,text="hello world")
        self.helloLabel.pack()
        self.quitButton=Button(self,text="quit",command=self.hello)
        self.quitButton.pack()
    def hello(self):
        name=self.input.get()
        messagebox.showinfo('message','hello %s'% name)


if __name__=="__main__":
        app=gui()
        app.master.title('demo')
        app.mainloop()

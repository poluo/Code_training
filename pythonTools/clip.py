#!/usr/bin/python
# -*- coding: UTF-8 -*-

# **********************************************************
# * Author        : poluo
# * Email         : xxx@email.com
# * Create time   : 2016-11-03 15:17
# * Last modified : 2016-11-03 15:17
# * Filename      : clip.py
# * Description   :get content from clip,not support linux,just in win,for now 
# **********************************************************
import pyperclip
def get_clip():
    return pyperclip.paste()

if __name__=='__main__':
    print(get_clip())
    c=input('Enter any key to end')

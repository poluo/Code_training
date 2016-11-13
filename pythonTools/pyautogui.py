import pyautogui
import time
#get screen size
width,height=pyautogui.size()
#get position
pos=pyautogui.position()
#click mouse right key
pyautogui.click(22,21,button='left')
# moves mouse to X of 100, Y of 200 over 2 seconds
pyautogui.moveTo(100, 200, 2)
# drag mouse to X of 100, Y of 200 while holding down left mouse button
pyautogui.dragTo(100, 200, button='left')
pyautogui.scroll(10)
try:
    while True:
        x,y=pyautogui.position()
        pyautogui.typewrite('hello world')
except KeyboardInterrupt:
    print('Done')
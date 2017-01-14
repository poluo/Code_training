from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
import time

path="C:\Program Files (x86)\Google\Chrome\chromedriver"
driver = webdriver.Chrome(executable_path=path)
# driver = webdriver.PhantomJS()
#driver = webdriver.Firefox()
driver.get("http://music.163.com")
print(driver.title)
# 查询页面中的元素 一次查找多个元素 (这些方法会返回一个list列表):
# find_elements_by_name
# find_elements_by_xpath
# find_elements_by_link_text
# find_elements_by_partial_link_text
# find_elements_by_tag_name
# find_elements_by_class_name
# find_elements_by_css_selector

driver.switch_to_frame("g_iframe")
#print(driver.page_source)
#driver.switch_to_default_content()
try:
    element = WebDriverWait(driver, 10).until(
        EC.presence_of_element_located((By.ID, "side-download"))
    )
    element.click()
except Exception as e:
    print(e)

# elem.clear()
# #发送一个关键字
# elem.send_keys("胡歌")
# elem.send_keys(Keys.RETURN)
#assert "No results found." not in driver.page_source
time.sleep(30)
#quit 将关闭整个浏览器，而`close`只会关闭一个标签页
driver.close()
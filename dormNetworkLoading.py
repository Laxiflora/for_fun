#用於監控中正大學宿舍網站流量
#當超過一定的值將會跳出警告
#作者:資管三 劉宇承

import requests
from bs4 import BeautifulSoup
import html5lib
import time
def flowFetch(url):
  html = requests.get(url).text
  soup = BeautifulSoup(html,'html5lib')
  wired_flow = soup.find('h3').get_text()
  total_flow = [a.get_text() for a in soup('h2') if a.has_attr('style')]
  return (wired_flow,total_flow[0])


def overFlow(limitFlow,actualFlow):  #檢測本日流量是否超標
  return limitFlow <= ''.join([x for x in actualFlow if x.isdigit() or x=='.'])

def caution():
  #超出流量的警告用函數,可以自訂化實作
  print("今天網路用夠多了")

url = "https://dglow.dorm.ccu.edu.tw/flows/"
your_IP = input("輸入你要監控的宿舍IP:")
url+=your_IP
limitFlow = input("輸入你的容許流量上限(單位是GB):")
while True:
  result = flowFetch(url)
  print(result[0]+"\n"+result[1])
  if overFlow(limitFlow,result[1]):
    caution()  
  time.sleep(5)   #幾秒去刷一次流量
import requests
import json

payload={}
headers = {}


forum_req = "https://www.dcard.tw/_api/forums/pet/posts?popular=false"
response = requests.request("GET", forum_req, headers=headers, data=payload)
forum_dict = json.loads(response.text)
id = []     #文章id列表

for _id in forum_dict:
  id.append(_id['id'])


for _id in id:
  url = "https://www.dcard.tw/_api/posts/"+str(_id)
  payload={}
  headers = {}
  response = requests.request("GET", url,headers=headers, data=payload)
  data = json.loads(response.text)
  print("文章{}中的圖片如下:".format(_id))
  print("",end = "\t")
  for img in data['media']:
      print(img['url'])



#print(response.text)

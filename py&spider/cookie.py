#登录得到cookie
#带着cookie去爬虫
#这两步必须同时开始

#用session(会话)
import requests

session = requests.Session()
data={}#form data里面的键值对
url = ""#模拟登录
session.post(url,data=data)
#print(session.post(url,data=data).cookie)

#拿数据
res =session.get('')#里面填写你要的数据的网址
res.json()#json form print

#使用requests要加上cookie

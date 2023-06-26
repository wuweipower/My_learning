#from urllib.request import urlopen

#url = "http://www.baidu.com"
#res = urlopen(url)

#print(res.read().decode("utf-8"))

'''
请求头中
User-Agent:请求载体的身份标识(用什么发送的请求)
Referer:防盗链(这次请求从哪个页面来的？反爬会用到)
cookie:本地字符串数据信息(用户登录信息，反爬的token)

GET:显示提交
POST:隐式提交
'''



import requests
headers = {
    "User-Agent":"Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:98.0) Gecko/20100101 Firefox/98.0"
}
res = requests.get("https://webfs.ali.kugou.com/202203221714/c7679dbde636b530b1db910f12aed5c6/part/0/960115/KGTX/CLTX001/6d6bc2d6ae2b21943f810a2cd23e2260.mp3",headers = headers)
res.encoding = "uft-8"
with open("a.mp3",mode='wb') as f:
    f.write(res.content)

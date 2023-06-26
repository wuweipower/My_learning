
import requests
'''
url = "http://www.runoob.com/wp-content/themes/runoob/assets/img/404.jpg"
response=requests.get(url)
with open('img.jpg',mode='wb') as f:
    f.write(response.content)
'''
url = "http://www.baidu.com"
headers={
    "User-Agent":"Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:98.0) Gecko/20100101 Firefox/98.0"
}#处理反爬，伪装成浏览器
#res = requests.get(url,headers = headers)
#print(res.text)#html文件 源码
dic={

}
#res = requests.post(url,data = dic)#发送的数据必须放在字典中，key和value的格式根据浏览器抓包查询
#res.json()

url="https://gimg2.baidu.com/image_search/src=http%3A%2F%2Fnimg.ws.126.net%2F%3Furl%3Dhttp%253A%252F%252Fdingyue.ws.126.net%252F2021%252F1102%252F93975e08j00r1xt2q000zc000hs00a1g.jpg%26thumbnail%3D650x2147483647%26quality%3D80%26type%3Djpg&refer=http%3A%2F%2Fnimg.ws.126.net&app=2002&size=f9999,10000&q=a80&n=0&g=0n&fmt=auto?sec=1651677114&t=e7059f45461277fb0a43adf0e93c79e1"
res = requests.get(url,headers=headers)
with open('a.jpg',mode='wb') as f:
    f.write(res.content)


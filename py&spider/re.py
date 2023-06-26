import re
lst = re.findall("\\d+","w10")#多加一个转义字符来表示\d 正则表达
lst = re.findall(r"\d+","w10a1001")
print(lst)

it =re.finditer(r"\d+","w10a1001")
for i in it:
    print(i)
    print(i.group())

it =re.search(r"\d+","w10a1001")#只返回第一个
print(it.group)

#match函数从头开始

obj = re.compile(r"\d")#直接预加载
#obj.findall()
s = ""
#.*?尽可能少的匹配

#(?P<分组名字>正则)可以单独从正则匹配的内容中进一步提取内容
obj = re.compile(r"<div><span id='(?P<id>\d+)'>(?P<name>.*?)</span></div>",re.S) #re.S能使.匹配到换行符
res = obj.finditer(s)#在s中匹配
for i in res:
    print(i.group("id"))
    print(i.group("name"))
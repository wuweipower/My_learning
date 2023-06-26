import requests
from bs4 import BeautifulSoup

url = ""
res = requests.get(url)
res.encoding = "utf-8"

main_page = BeautifulSoup(res.text,"html.parser")
alist = main_page.find("div",class_="Type").find_all("a")
for a in alist:
    href = a.get("href")
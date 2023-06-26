import requests

proxies={
    "https":"https://"
}

res = requests.get("https://www.baidu.com",proxies=proxies)

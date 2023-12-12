import requests
from bs4 import BeautifulSoup
import lxml


def get_group(url):
    src=url["href"]
    return src[16::]


def make_institute_links(url_list):
    for x in range(1,15):
        if x!=13:
            url_list.append(f"https://mai.ru/education/studies/schedule/groups.php?department=Институт+№{x}&course=all")
    return url_list


def make_all_group_dict():
    url_list=[]
    group_dict={}
    cnt=0
    institute_links=make_institute_links(url_list)
    for url in institute_links:
        if cnt==13: cnt+=2
        else:cnt+=1
        req = requests.get(url)
        req.encoding='utf-8'
        src=req.text
        soup = BeautifulSoup(src, 'lxml')
        mydivs = soup.find_all("a", {"class": "btn btn-soft-secondary btn-xs mb-1 fw-medium btn-group"})
        group_list=[get_group(url) for url in mydivs]
        group_dict[cnt]=group_list
    return group_dict


def get_group_timetable():
    group_dict=make_all_group_dict()
    lst=[]
    for key in group_dict:
        for group in group_dict[key]:
            url="https://mai.ru/education/studies/schedule/index.php?group="+group
            lst.append(url)
    return lst


def main():
    url_list=get_group_timetable()
    for url in url_list:
        print(url)
        for week in range(14,15):
            url+= f"&week={week}"
            print(url)
            req = requests.get(url)
            req.encoding='utf-8'
            src=req.text
            soup = BeautifulSoup(src,'lxml')
            table = soup.find_all("ul", {"class": 'step mb-5'})
            print(table)
            return
if __name__=='__main__':
    main()
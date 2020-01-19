import urllib.request as rq
import re
import threading as th

def get_as_txt(url):
    text = ""
    with rq.urlopen(url.replace("\"", "")) as response:
        for line in response:
            text += line.decode("utf-8")
    return text

def unique(list1):
    unique_list = []
    for x in list1:
        if x not in unique_list:
            unique_list.append(x)
    return unique_list

def pageSearch(url, word):
    text = get_as_txt(url)
    return text.count(word)

def searchForWord(url, distance, action, results, word):
    page_text = get_as_txt(url)
    print("Calculate link: ", url)
    results[url] = action(url, word)
    if distance == 0:
        return
    a_marker = re.findall(r"\<a\shref=\"http[^\"]*\"", page_text)
    links = []
    for link in a_marker:
        links.extend(re.findall(r"\".*[^\.svg]\"", link))
    hyperlinks = unique(links)
    for link in hyperlinks:
        if not link in results.keys():
            if th.active_count == 6:
                th.current_thread().join()
            t = th.Thread(target=searchForWord, args=[link, distance - 1, action, results, word])
            t.start()

def crawl_iterator(start_page, distance, action):
    dict_of_results = {}
    t = th.Thread(target=searchForWord, args=[start_page, distance, action, dict_of_results, "Python"])
    t.start()
    while len(th.enumerate()) > 1:
        pass
    for res in dict_of_results.items():
        yield res

def crawl(start_page, distance, action):
    count = 0
    for res in crawl_iterator(start_page, distance, action):
        count += res[1]
    return count

# print(crawl("https://www.python.org/", 0, pageSearch))
print(crawl("https://www.python.org/", 1, pageSearch))

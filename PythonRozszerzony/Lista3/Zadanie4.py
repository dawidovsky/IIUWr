import random


def uprosc_zdanie(tekst, dl_slowa, liczba_slow):
    tab = tekst.split(' ')
    res = list(filter(lambda st: len(st) < dl_slowa, tab))
    res = list(filter(bool, res))
    while len(res) > liczba_slow:
        rnd = random.randint(0, len(res)-1)
        res.remove(res[rnd])
    return ' '.join(res)


text = "Podział peryklinalny inicjałów wrzecionowatych \
        kambium charakteryzuje się ścianą podziałową inicjowaną \
        w płaszczyźnie maksymalnej."

text2 = "Lorem ipsum dolor sit amet, consectetur adipiscing elit.\
        Vestibulum molestie dui diam, lobortis viverra felis tincidunt\
        eget. Ut tincidunt augue a velit mollis semper. Fusce at\
        facilisis orci. Vestibulum aliquet magna nec mi condimentum\
        semper. Pellentesque mauris lorem, pretium ut bibendum in,\
        euismod vel arcu. Nulla et est vitae velit aliquet placerat.\
        Etiam ut scelerisque mauris, nec accumsan diam. Nam ante lorem,\
        aliquam ut molestie vitae, commodo eu diam. Cras vitae neque\
        vitae turpis ultrices placerat et sit amet nisi. Duis nec\
        pharetra diam. Cras finibus interdum aliquet."

print(uprosc_zdanie(text2, 10, 5))

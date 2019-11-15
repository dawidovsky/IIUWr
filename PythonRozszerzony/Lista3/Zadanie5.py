def kompresja(tekst):
    tmp = tekst[0]
    count = 1
    res = ""
    for char in tekst[1:]:
        if char == tmp:
            count += 1
        elif count > 1:
            res += str(count) + tmp
            count = 1
        else:
            res += tmp
        tmp = char
    if count > 1:
        res += str(count) + tmp
    else:
        res += tmp
    return res


def dekompresja(tekst_skompresowany):
    res = ""
    for i in range(len(tekst_skompresowany)):
        if tekst_skompresowany[i].isdigit():
            i += 1
            for _ in range(int(tekst_skompresowany[i-1])):
                res += tekst_skompresowany[i]
        else:
            res += tekst_skompresowany[i]
    return res


print(kompresja("suuuuper"))
print(kompresja("aaaaaa"))

print(dekompresja("s4uper"))
print(dekompresja("6a"))

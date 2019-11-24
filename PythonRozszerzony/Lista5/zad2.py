import itertools as it

def unique(list1):
    unique_list = []
    for x in list1:
        if x not in unique_list:
            unique_list.append(x)
    return unique_list

def flatten(list1):
    flat_list = []
    for sublist in list1:
        for item in sublist:
            flat_list.append(item)
    return flat_list

def krypt(str1, str2, res_str):
    perm = list(it.permutations(range(10), 10))
    letters = []
    letters.append(list(str1))
    letters.append(list(str2))
    letters.append(list(res_str))
    letters = unique(flatten(letters))
    res = dict(zip(letters, perm[0]))

    tmp_str1 = str1
    tmp_str2 = str2
    tmp_res = res_str

    for fr, to in res.items():
        tmp_str1 = tmp_str1.replace(fr, str(to))
        tmp_str2 = tmp_str2.replace(fr, str(to))
        tmp_res = tmp_res.replace(fr, str(to))

    i = 1
    while int(tmp_str1) + int(tmp_str2) != int(tmp_res):
        tmp_str1 = str1
        tmp_str2 = str2
        tmp_res = res_str
        res = dict(zip(letters, perm[i]))
        for fr, to in res.items():
            tmp_str1 = tmp_str1.replace(fr, str(to))
            tmp_str2 = tmp_str2.replace(fr, str(to))
            tmp_res = tmp_res.replace(fr, str(to))
        i += 1
    return res

# print(krypt("KIOTO", "OSAKA", "TOKIO"))
print(krypt("KTO", "KOT", "TOK"))
# print(krypt("TRZY", "TRZY", "SZESC"))
# print(krypt("CHMURA", "CHMURA", "DESZCZ"))

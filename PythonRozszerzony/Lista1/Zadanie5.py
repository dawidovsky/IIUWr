def rozklad(n):
    if n == 1:
        return [(1, 1)]
    res = []
    i = 2
    count = 0
    while n > 1:
        while n % i == 0:
            count += 1
            n /= i
        if count > 0:
            res.append((i, count))
        count = 0
        i += 1
    return res


print(rozklad(756))
print(rozklad(0))
print(rozklad(1))
print(rozklad(123321))
print(rozklad(13063))

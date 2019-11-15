def pierwiastek(n):
    res = 0
    for i in range(1, n+1):
        res += 2*i - 1
        if res > n:
            return i-1


print(pierwiastek(4))
print(pierwiastek(9))
print(pierwiastek(25))
print(pierwiastek(50))
print(pierwiastek(110))

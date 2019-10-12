def romb(n):
    for i in range(n+1):
        for _ in range(n-i):
            print(' ', end='')
        for _ in range(i*2+1):
            print('#', end='')
        print()
    for i in range(n):
        for _ in range(i+1):
            print(' ', end='')
        for _ in range(2*(n-i)-1):
            print('#', end='')
        print()


romb(4)
print()
romb(6)
print()

import math
import timeit
from tabulate import tabulate

def czy_pierwsza(n):
	for i in range(2, math.floor(math.sqrt(n)) + 1):
		if n%i == 0:
			return False
	return True

def pierwsze_imperatywna(n):
	res = []
	for i in range(2, n+1):
		is_prime = True
		for j in range(2, i):
			if i%j == 0:
				is_prime = False
		if is_prime:
			res.append(i)
	return res

def pierwsze_iterator(n):
    for i in range(2, n+1):
        if czy_pierwsza(i):
            yield i

def iterator(n):
    res = []
    for i in pierwsze_iterator(n):
        res.append(i)
    return res

def pierwsze_skladana(n):
	return [i for i in range(2, n+1) if all(i % j != 0 for j in range(2, i))]

def pierwsze_funkcyjna(n):
	return list(filter(lambda x: czy_pierwsza(x), range(2, n+1)))

def time_im(i, n):
    return timeit.timeit("pierwsze_imperatywna(" + i + ")", setup= "from __main__ import pierwsze_imperatywna", number=n)

def time_sk(i, n):
    return timeit.timeit("pierwsze_skladana(" + i + ")", setup= "from __main__ import pierwsze_skladana", number=n)

def time_fn(i, n):
    return timeit.timeit("pierwsze_funkcyjna(" + i + ")", setup= "from __main__ import pierwsze_funkcyjna", number=n)

def time_it(i, n):
    return timeit.timeit("iterator(" + i + ")", setup= "from __main__ import iterator", number=n)

names = ["number", "imperatywna", "skladana", "funkcyjna", "iterowana"]
print(tabulate([[10, time_im("20", 10), time_sk("20", 10), time_fn("20", 10), time_it("20", 10)],
                [100, time_im("20", 100), time_sk("20", 100), time_fn("20", 100), time_it("20", 100)],
                [1000, time_im("20", 1000), time_sk("20", 1000), time_fn("20", 1000), time_it("20", 1000)]
    ], headers=names, tablefmt="github"))

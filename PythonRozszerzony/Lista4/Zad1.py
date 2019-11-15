import math
import timeit

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

def pierwsze_skladana(n):
	return [i for i in range(2, n+1) if all(i % j != 0 for j in range(2, i))]

def pierwsze_funkcyjna(n):
	return list(filter(lambda x: czy_pierwsza(x), range(2, n+1)))

print("Imperatywna: ",timeit.timeit("pierwsze_imperatywna(20)", setup= "from __main__ import pierwsze_imperatywna", number=100000))
print("Skladana: ",timeit.timeit("pierwsze_skladana(20)", setup= "from __main__ import pierwsze_skladana", number=100000))
print("Funkcyjna: ",timeit.timeit("pierwsze_funkcyjna(20)", setup= "from __main__ import pierwsze_funkcyjna", number=100000))

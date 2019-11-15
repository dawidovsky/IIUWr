import timeit

def sumadzielinkow(n):
    suma = 0
    for i in range(1, n//2+1):
        if n % i == 0:
            suma += i
    return suma

def doskonala(n):
    return sumadzielinkow(n) == n

def doskonale_imperatywna(n):
	res = []
	for i in range(6, n+1):
		suma = 0
		for j in range(1, i//2+1):
			if i % j == 0:
				suma += j
		if suma == i:
			res.append(i)
	return res

def doskonale_skladane(n):
	return [i for i in range(6, n+1) if sum(j for j in range(1, i//2+1) if i%j == 0) == i]

def doskonale_funkcyjne(n):
	return list(filter(lambda x : doskonala(x), range(6, n+1)))

print("Imperatywna: ",timeit.timeit("doskonale_imperatywna(5000)", setup= "from __main__ import doskonale_imperatywna", number=20))
print("Skladana: ",timeit.timeit("doskonale_skladane(5000)", setup= "from __main__ import doskonale_skladane", number=20))
print("Funkcyjna: ",timeit.timeit("doskonale_funkcyjne(5000)", setup= "from __main__ import doskonale_funkcyjne", number=20))

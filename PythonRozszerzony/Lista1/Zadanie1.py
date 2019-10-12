def vat_faktura(list):
    return sum(list) * 0.23


def vat_paragon(list):
    return sum(map((lambda x: x * 0.23), list))


prices = [0.2, 0.5, 4.59, 6]
print("faktura: ", vat_faktura(prices))
print("paragon: ", vat_paragon(prices))
print("compare: ", vat_faktura(prices) == vat_paragon(prices))
prices = [5, 6, 1, 3, 5]
print("faktura: ", vat_faktura(prices))
print("paragon: ", vat_paragon(prices))
print("compare: ", vat_faktura(prices) == vat_paragon(prices))
prices = [0.01 ] * 100
print(vat_faktura(prices))
print(vat_paragon(prices))
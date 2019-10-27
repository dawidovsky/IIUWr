import itertools


class Formula:
    pass


class Zmienna(Formula):
    def __init__(self, nazwa):
        self.nazwa = nazwa

    def oblicz(self, zmienne):
        return bool(zmienne[self.nazwa])

    def __str__(self):
        return self.nazwa


class Falsz(Formula):
    def oblicz(self, zmienne):
        return False

    def __str__(self):
        return "false"


class Prawda(Formula):
    def oblicz(self, zmienne):
        return True

    def __str__(self):
        return "true"


class And(Formula):
    def __init__(self, lewa, prawa):
        self.lewa = lewa
        self.prawa = prawa

    def oblicz(self, zmienne):
        return self.lewa.oblicz(zmienne) and self.prawa.oblicz(zmienne)

    def __str__(self):
        return "(" + str(self.lewa) + " & " + str(self.prawa) + ")"


class Or(Formula):
    def __init__(self, lewa, prawa):
        self.lewa = lewa
        self.prawa = prawa

    def oblicz(self, zmienne):
        return self.lewa.oblicz(zmienne) or self.prawa.oblicz(zmienne)

    def __str__(self):
        return "(" + str(self.lewa) + " | " + str(self.prawa) + ")"


class Imp(Formula):
    def __init__(self, lewa, prawa):
        self.lewa = lewa
        self.prawa = prawa

    def oblicz(self, zmienne):
        return not(self.lewa.oblicz(zmienne)) or self.prawa.oblicz(zmienne)

    def __str__(self):
        return "(" + str(self.lewa) + " => " + str(self.prawa) + ")"


class Neg(Formula):
    def __init__(self, formula):
        self.formula = formula

    def oblicz(self, zmienne):
        return not(self.formula.oblicz(zmienne))

    def __str__(self):
        return "~(" + str(self.formula) + ")"


class Rownowaznosc(Formula):
    def __init__(self, lewa, prawa):
        self.lewa = lewa
        self.prawa = prawa

    def oblicz(self, zmienne):
        return (not(self.lewa.oblicz(zmienne)) or self.prawa.oblicz(zmienne)) \
            and (not(self.prawa.oblicz(zmienne)) or self.lewa.oblicz(zmienne))

    def __str__(self):
        return "(" + str(self.lewa) + " <=> " + str(self.prawa) + ")"


def isTautology(formula):
    values = [True, False]
    possibilities = list(itertools.product(values, repeat=len(zmienne)))
    for poss in possibilities:
        new_dict = {}
        i = 0
        for key in zmienne:
            new_dict[key] = poss[i]
            i += 1
        if(not formula.oblicz(new_dict)):
            return "Not Tautology"
    return "Tautology"


zmienne = {"x": False, "y": False, "z": False}
# f = Imp(Zmienna("x"), And(Zmienna("y"), Prawda()))
# f = Or(Zmienna("x"), Neg(Zmienna("x")))
# f = Rownowaznosc(Imp(Zmienna("x"), Zmienna("y")), Imp(Neg(Zmienna("y")), Neg(Zmienna("x"))))
f = Imp(And(Zmienna("x"), Zmienna("y")), Or(Zmienna("z"), Zmienna("x")))
print(str(f))
print(f.oblicz(zmienne))
print(isTautology(f))

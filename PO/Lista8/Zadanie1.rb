# Dawid Paluszak
# Pracownia PO, czwartek, s. 108
# L8, z1, Rozszerzenie FixNum
# Zadanie1.rb
# Zadanie1.rb
# 2018-04-19

class Fixnum
  # liczenie ackermana
    def ack (m)
        if self==0
            m+1
        elsif m==0
            (self-1).ack(1)
        else
            (self-1).ack(self.ack(m-1))
        end
    end
    # wyliczanie czynników
    def czynniki
        rezultat = []
        licznik = 0
        for i in 1..self do
            if self % i == 0
                rezultat[licznik] = i
                licznik += 1
                end
        end
        rezultat
    end
    # sprawdzanie czy liczba jest doskonała
    def doskonala
        resultat = 0
        for i in self.czynniki do
            if self != i
                resultat += i
            end
        end
        resultat == self
    end
    # zapisywanie liczb słownie w sposób prosty
    def slownie
        rezultat = ''
        for i in 0...self.to_s.length do
            case self.to_s[i]
            when '0'
                rezultat << ' zero'
            when '1'
                rezultat << ' jeden'
            when '2'
                rezultat << ' dwa'
            when '3'
                rezultat << ' trzy'
            when '4'
                rezultat << ' cztery'
            when '5'
                rezultat << ' piec'
            when '6'
                rezultat << ' szesc'
            when '7'
                rezultat << ' siedem'
            when '8'
                rezultat << ' osiem'
            when '9'
                rezultat << ' dziewiec'
            end
        end
        rezultat
    end
end

puts "Ackerman od 2 = #{2.ack(1)}"
puts "Czynniki 6 to #{6.czynniki}"
puts "Czy 6 jest doskonala - #{28.doskonala}"    # 1 + 2 + 3 = 6 (dzielniki = liczba)
puts "Slownie liczba 42 to #{42.slownie}"

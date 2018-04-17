class Fixnum
    def ack (m)
        if self==0
            m+1
        elsif m==0
            (self-1).ack(1)
        else
            (self-1).ack(self.ack(m-1))
        end
    end
    def czynniki
        @@rezultat = []
        @@licznik = 0
        for i in 1..self do
            if self % i == 0
                @@rezultat[@@licznik] = i
                @@licznik += 1
                end
        end
        @@rezultat
    end
    def doskonala
        @@resultat = 0
        for i in self.czynniki do
            if self != i
                @@resultat += i
            end
        end
        @@resultat == self
    end

    def slownie
        @@rezultate = ''
        for i in 0...self.to_s.length do
            case self.to_s[i]
            when '0'
                @@rezultate << ' zero'
            when '1'
                @@rezultate << ' jeden'
            when '2'
                @@rezultate << ' dwa'
            when '3'
                @@rezultate << ' trzy'
            when '4'
                @@rezultate << ' cztery'
            when '5'
                @@rezultate << ' piec'
            when '6'
                @@rezultate << ' szesc'
            when '7'
                @@rezultate << ' siedem'
            when '8'
                @@rezultate << ' osiem'
            when '9'
                @@rezultate << ' dziewiec'
            end
        end
        @@rezultate
    end
end

puts "ackerman od 2 = #{2.ack(1)}"
puts "czynniki 6 to #{6.czynniki}"
puts "doskonalosc liczby 7 #{7.doskonala}"
puts "ona musi 6 #{6.doskonala}"
puts "slownie liczba 42 =#{42.slownie}"

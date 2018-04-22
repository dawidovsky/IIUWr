# Dawid Paluszak
# Pracownia PO, czwartek, s. 108
# L8, z3, Szyfrowanie
# Zadanie3.rb
# Zadanie3.rb
# 2018-04-19

class Jawna
  def initialize(nazwa,klucz)
    @nazwa = nazwa
    @klucz = klucz
    # deszyfrowanie
    for i in 0...@nazwa.length
      @nazwa[i] = @klucz.invert[@nazwa[i]]
    end
  end
  def to_s
    @nazwa
  end
  def zaszyfruj(klucz)
    Zaszyfrowane.new(@nazwa,klucz)
  end
end

class Zaszyfrowane
  def initialize(nazwa,klucz)
    @nazwa = nazwa
    @klucz = klucz
    # szyfrowanie
    for i in 0...@nazwa.length
      @nazwa[i] = @klucz[@nazwa[i]]
    end
  end
  def to_s
    @nazwa
  end
  def odszyfruj(klucz)
    Jawne.new(@nazwa,@klucz)

  end
end
klucz = {
  'a' => 'b',
  'b' => 'c',
  'c' => 'd',
  'd' => 'e',
  'f' => 'g'
}
puts "Szyfruje abcdfaa"
szyfr = Zaszyfrowane.new("abcdfaa",klucz)
puts "Zaszyfrowane #{szyfr}"
puts "Odszyfrowane #{Jawna.new("bcdegbb",klucz)}"

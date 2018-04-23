require 'test/unit'

def palindrome(n)
  n.downcase.tr('^a-z','') == n.downcase.tr('^a-z','').reverse
end

puts "Palindrom"
puts palindrome("A man, a plan, a canal -- Panama")
puts palindrome("Madam, I'm Adam!")
puts palindrome("Abracadabra")
puts palindrome("")

def count_words(n)
  hash = Hash.new
  arr = n.downcase.tr('^a-z ','').split(" ")
  for i in arr
    if(hash.has_key?(i))
      ile = hash[i]
      ile += 1
      hash.update({i => ile})
    else
      hash.store(i,1)
    end
  end
  hash
end

puts "Count Words"
puts count_words("A man, a plan, a canal -- Panama")

def same23?(n)
  if(n.count != 5)
    return false
  end
  n.sort!
  (n[0] == n[1] and n[0] == n[2] and n[3] == n[4] and n[0] != n[4]) or (n[0] == n[1] and n[2] == n[3] and n[2] == n[4] and n[0] != n[4])
end

puts same23?(["a", "a", "a", "b", "b"])
puts same23?(["a", "b", "c", "b", "c"])
puts same23?(["a", "a", "a", "a", "a"])
puts same23?(["a", "b", "a", "b", "a"])
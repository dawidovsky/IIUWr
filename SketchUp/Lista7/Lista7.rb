require 'test/unit'

def palindrome(n)
  n.downcase.tr('^a-z','') == n.downcase.tr('^a-z','').reverse
end

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

def same23?(n)
  a = b = c = 0
  for i in n
    if(i == 'a')
        a += 1
    elsif(i == 'b')
      b += 1
    else
      c += 1
    end
  end
  ((a == 3 &&( b == 2 || c == 2)) || (b == 3 && (a == 2 || c == 2)) || (c == 3 && (b == 2 || a == 2)))
end

class Testing < Test::Unit::TestCase
  def test1
    puts "Palindrom"
    assert_equal(palindrome("A man, a plan, a canal -- Panama"),true)
    assert_equal(palindrome("Madam, I'm Adam!"),true)
    assert_equal(palindrome("Abracadabra"),false)
    assert_equal(palindrome(""),true)
  end
  def test2
    puts "Count Words"
    assert_equal(count_words("A man, a plan, a canal -- Panama"), {'a' => 3, 'man' => 1, 'canal' => 1, 'panama' => 1, 'plan' => 1})
  end
  def test3
    puts "Same23?"
    assert_equal(same23?(["a", "a", "a", "b", "b"]),true)
    assert_equal(same23?(["a", "b", "c", "b", "c"]),false)
    assert_equal(same23?(["a", "a", "a", "a", "a"]),false)
    assert_equal(same23?(["a", "b", "a", "b", "a"]),true)
  end
end

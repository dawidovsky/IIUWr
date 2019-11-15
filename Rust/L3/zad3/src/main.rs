fn main(){}

struct Cipher {
  first_code: String,
  second_code: String
}

impl Cipher {
  fn new(map1: &str, map2: &str) -> Cipher {
    Cipher {
        first_code: map1.to_string(),
        second_code: map2.to_string(),
      }
  }

  fn encode(&self, string: &str) -> String {
    code(&*self.first_code.to_string(), &*self.second_code.to_string(), string)
  }

  fn decode(&self, string: &str) -> String {
    code(&*self.second_code.to_string(), &*self.first_code.to_string(), string)
  }

}
  fn code(from: &str, to: &str, string: &str) -> String {
    let mut new_string: String = "".to_string();
    for c in string.chars() {
        let index = from.chars().position(|x| x == c);
        if index.is_none() {
            new_string.push(c);
        }
        else{
            new_string.push(to.chars().nth(index.unwrap()).unwrap());
        }
    }
    new_string
  }

#[test]
fn test1() {
  let map1 = "abcdefghijklmnopqrstuvwxyz";
  let map2 = "etaoinshrdlucmfwypvbgkjqxz";

  let cipher = Cipher::new(map1, map2);

  assert_eq!(cipher.encode("abc"), "eta");
}

#[test]
fn test2() {
  let map1 = "abcdefghijklmnopqrstuvwxyz";
  let map2 = "etaoinshrdlucmfwypvbgkjqxz";

  let cipher = Cipher::new(map1, map2);

  assert_eq!(cipher.encode("xyz"), "qxz");
}

#[test]
fn test3() {
  let map1 = "abcdefghijklmnopqrstuvwxyz";
  let map2 = "etaoinshrdlucmfwypvbgkjqxz";

  let cipher = Cipher::new(map1, map2);

  assert_eq!(cipher.decode("eirfg"), "aeiou");
}

#[test]
fn test4() {
  let map1 = "abcdefghijklmnopqrstuvwxyz";
  let map2 = "etaoinshrdlucmfwypvbgkjqxz";

  let cipher = Cipher::new(map1, map2);

  assert_eq!(cipher.decode("erlang"), "aikcfu");
}

#[test]
fn test5() {
  let map1 = "abcdefghijklmnopqrstuvwxyz";
  let map2 = "etaoinshrdlucmfwypvbgkjqxz";

  let cipher = Cipher::new(map1, map2);

  assert_eq!(cipher.encode("aigj"), "ersd");
}

#[test]
fn test6() {
  let map1 = "abcdefghijklmnopqrstuvwxyz";
  let map2 = "etaoinshrdlucmfwypvbgkjqxz";

  let cipher = Cipher::new(map1, map2);

  assert_eq!(cipher.decode("ang"), "cfu");
}

#[test]
fn test7() {
  let map1 = "abcdefghijklmnopqrstuvwxyz";
  let map2 = "etaoinshrdlucmfwypvbgkjqxz";

  let cipher = Cipher::new(map1, map2);

  assert_eq!(cipher.encode("erl"), "ipu");
}

#[test]
fn test8() {
  let map1 = "abcdefghijklmnopqrstuvwxyz";
  let map2 = "etaoinshrdlucmfwypvbgkjqxz";

  let cipher = Cipher::new(map1, map2);

  assert_eq!(cipher.decode(""), "");
}

#[test]
fn test9() {
  let map1 = "abcdefghijklmnopqrstuvwxyz";
  let map2 = "etaoinshrdlucmfwypvbgkjqxz";

  let cipher = Cipher::new(map1, map2);

  assert_eq!(cipher.decode("a"), "c");
}

#[test]
fn test10() {
  let map1 = "abcdefghijklmnopqrstuvwxyz";
  let map2 = "etaoinshrdlucmfwypvbgkjqxz";

  let cipher = Cipher::new(map1, map2);

  assert_eq!(cipher.decode("xds"), "yjg");
}
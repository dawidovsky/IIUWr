fn main() {}

fn get_count(string: &str) -> usize {
    let mut vowels_count: usize = 0;
    string.chars().for_each(|c| { if vec!['a', 'e', 'i', 'o', 'u'].contains(&c) {vowels_count += 1} });
    vowels_count
}

#[test]
fn test1() {
  assert_eq!(get_count("abracadabra"), 5);
}

#[test]
fn test2() {
  assert_eq!(get_count("o a kak ushakov lil vo kashu kakao"), 13);
}

#[test]
fn test3() {
  assert_eq!(get_count(""), 0);
}

#[test]
fn test4() {
  assert_eq!(get_count("qwr"), 0);
}

#[test]
fn test5() {
  assert_eq!(get_count("something"), 3);
}

#[test]
fn test6() {
  assert_eq!(get_count("oops"), 2);
}

#[test]
fn test7() {
  assert_eq!(get_count("teear"), 3);
}

#[test]
fn test8() {
  assert_eq!(get_count("aaaa"), 4);
}

#[test]
fn test9() {
  assert_eq!(get_count("aieou"), 5);
}

#[test]
fn test10() {
  assert_eq!(get_count(""), 0);
}
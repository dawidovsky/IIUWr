fn main(){}

fn string_to_number(s: &str) -> i32 {
  s.parse().unwrap()
}

#[test]
fn test1() {
    assert_eq!(string_to_number("123"), 123);
}

#[test]
fn test2() {
    assert_eq!(string_to_number("0"), 0);
}

#[test]
fn test3() {
    assert_eq!(string_to_number("12345"), 12345);
}

#[test]
fn test4() {
    assert_eq!(string_to_number("-321"), -321);
}

#[test]
fn test5() {
    assert_eq!(string_to_number("-123"), -123);
}
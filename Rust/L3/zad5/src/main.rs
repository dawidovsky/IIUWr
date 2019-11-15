fn main() {}

fn last_digit(str1: &str, str2: &str) -> i32 {
    if str2 == "0" {return 1}
    let last_digit: i32 = str1[str1.len().saturating_sub(1)..].parse::<i32>().unwrap();
    if last_digit == 0 {return 0}
    let mut two_digits: u32 = str2[str2.len().saturating_sub(2)..].parse::<u32>().unwrap() % 4;
    if two_digits == 0 {two_digits = 4}
    last_digit.pow(two_digits) % 10
}

#[test]
fn test1() {
  assert_eq!(last_digit("4", "1"), 4);
}

#[test]
fn test2(){
  assert_eq!(last_digit("9", "7"), 9);
}

#[test]
fn test3(){
  assert_eq!(last_digit("10","10000000000"), 0);
}

#[test]
fn test4(){
  assert_eq!(last_digit("1606938044258990275541962092341162602522202993782792835301376","2037035976334486086268445688409378161051468393665936250636140449354381299763336706183397376"), 6);
}

#[test]
fn test5(){
  assert_eq!(last_digit("3715290469715693021198967285016729344580685479654510946723", "68819615221552997273737174557165657483427362207517952651"), 7);
}

#[test]
fn test6(){
  assert_eq!(last_digit("4", "2"), 6);
}

#[test]
fn test7(){
  assert_eq!(last_digit("4", "2"), 6);
}

#[test]
fn test8(){
  assert_eq!(last_digit("4", "2"), 6);
}

#[test]
fn test9(){
  assert_eq!(last_digit("4", "2"), 6);
}

#[test]
fn test10(){
  assert_eq!(last_digit("4", "2"), 6);
}
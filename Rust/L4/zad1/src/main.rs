fn main() {}

fn find_digit(num: i32, nth: i32) -> i32 {
    let number = if num < 0 {num * -1} else {num};
    let num_str = number.to_string();
    if nth <= 0 {return -1}
    if num_str.len() < nth as usize {return 0}
    num_str.chars().rev().nth((nth-1) as usize).unwrap() as i32 - '0' as i32
}

#[test]
fn test1() {
    assert_eq!(find_digit(0, 20), 0);
}

#[test]
fn test2() {
    assert_eq!(find_digit(129, 2), 2);
}

#[test]
fn test3() {
    assert_eq!(find_digit(-2825, 3), 8);
}

#[test]
fn test4() {
    assert_eq!(find_digit(5673, 4), 5);
}

#[test]
fn test5() {
    assert_eq!(find_digit(-456, 4), 0);
}

#[test]
fn test6() {
    assert_eq!(find_digit(65, 0), -1);
}

#[test]
fn test7() {
    assert_eq!(find_digit(24, -8), -1);
}

#[test]
fn test8() {
    assert_eq!(find_digit(23129, 2), 2);
}

#[test]
fn test9() {
    assert_eq!(find_digit(-9, 2), 0);
}

#[test]
fn test10() {
    assert_eq!(find_digit(33, 2), 3);
}
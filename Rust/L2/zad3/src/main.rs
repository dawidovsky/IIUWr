fn main() {}

fn summy(strng: &str) -> i32 {
    strng.split(' ').collect::<Vec<&str>>().iter().map(|val| val.parse::<i32>().unwrap()).sum()
}

#[test]
fn test1() {
    assert_eq!(summy("1 2 3"), 6);
}

#[test]
fn test2() {
    assert_eq!(summy("1 2 3 4 5"), 15);
}

#[test]
fn test3() {
    assert_eq!(summy("1 2 3 4"), 10);
}

#[test]
fn test4() {
    assert_eq!(summy("10 10"), 20);
}

#[test]
fn test5() {
    assert_eq!(summy("0 0"), 0);
}

#[test]
fn test6() {
    assert_eq!(summy("8 9"), 17);
}

#[test]
fn test7() {
    assert_eq!(summy("-5 5"), 0);
}

#[test]
fn test8() {
    assert_eq!(summy("12 1"), 13);
}

#[test]
fn test9() {
    assert_eq!(summy("2 2 2"), 6);
}

#[test]
fn test10() {
    assert_eq!(summy("10 0 10"), 20);
}
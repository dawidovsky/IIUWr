fn main() {}

fn fcn(n: i32) -> i64 {
    2_i64.pow(n as u32)
}

#[test]
fn test1() {
    assert_eq!(fcn(17), 131072);
}

#[test]
fn test2() {
    assert_eq!(fcn(8), 256);
}

#[test]
fn test3() {
    assert_eq!(fcn(7), 128);
}

#[test]
fn test4() {
    assert_eq!(fcn(6), 64);
}

#[test]
fn test5() {
    assert_eq!(fcn(5), 32);
}

#[test]
fn test6() {
    assert_eq!(fcn(4), 16);
}

#[test]
fn test7() {
    assert_eq!(fcn(3), 8);
}

#[test]
fn test8() {
    assert_eq!(fcn(2), 4);
}

#[test]
fn test9() {
    assert_eq!(fcn(1), 2);
}

#[test]
fn test10() {
    assert_eq!(fcn(0), 1);
}

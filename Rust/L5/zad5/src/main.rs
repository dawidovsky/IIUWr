fn main() {
    dbl_linear(2);
}

fn dbl_linear(n: u32) -> u32{
    if n == 0 { return 1 }
    let mut set = Vec::new();
    set.push(1);
    let mut pt1: usize = 0;
    let mut pt2: usize = 0;
    let mut equal_count = 0;
    while set.len() <= (n + equal_count) as usize {
        let value1 = 2 * set[pt1] + 1;
        let value2 = 3 * set[pt2] + 1;
        let mut min = value1;
        if value1 > value2 { min = value2; pt2 += 1 }
        else if value1 == value2 { equal_count += 1; pt1 += 1; pt2 += 1; }
        else { pt1 += 1; }
        set.push(min);
    }
    set[n as usize]
}

#[test]
fn test1() {
    assert_eq!(dbl_linear(10), 22);
}

#[test]
fn test2() {
    assert_eq!(dbl_linear(20), 57);
}

#[test]
fn test3() {
    assert_eq!(dbl_linear(30), 91);
}

#[test]
fn test4() {
    assert_eq!(dbl_linear(50), 175);
}

#[test]
fn test5() {
    assert_eq!(dbl_linear(100), 447);
}

#[test]
fn test6() {
    assert_eq!(dbl_linear(0), 1);
}

#[test]
fn test7() {
    assert_eq!(dbl_linear(1), 3);
}

#[test]
fn test8() {
    assert_eq!(dbl_linear(2), 4);
}

#[test]
fn test9() {
    assert_eq!(dbl_linear(3), 7);
}

#[test]
fn test10() {
    assert_eq!(dbl_linear(4), 9);
}
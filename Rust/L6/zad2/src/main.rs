fn main() {}

fn number_to_vec(n: i64) -> Vec<u32> {
    n.to_string().chars().map(|c| c.to_digit(10).unwrap()).collect()
}

fn dig_pow(n: i64, p: i32) -> i64 {
    let values = number_to_vec(n);
    let mut res: u128 = 0;
    let mut power: u32 = p as u32;
    for val in values {
        let high_val: u128 = val as u128;
        res += high_val.pow(power);
        power += 1;
    }
    if res%n as u128 == 0 { res as i64/n } else { -1 }
}

#[test]
fn test1() {
    assert_eq!(dig_pow(89, 1), 1);
}

#[test]
fn test2() {
    assert_eq!(dig_pow(92, 1), -1);
}

#[test]
fn test3() {
    assert_eq!(dig_pow(46288, 3), 51);
}

#[test]
fn test4() {
    assert_eq!(dig_pow(3, 1), 1);
}

#[test]
fn test5() {
    assert_eq!(dig_pow(123, 0), -1);
}

#[test]
fn test6() {
    assert_eq!(dig_pow(9, 4), 729);
}

#[test]
fn test7() {
    assert_eq!(dig_pow(24, 1), -1);
}

#[test]
fn test8() {
    assert_eq!(dig_pow(6, 1), 1);
}

#[test]
fn test9() {
    assert_eq!(dig_pow(2427, 1), 1);
}

#[test]
fn test10() {
    assert_eq!(dig_pow(3456789, 5), -1);
}
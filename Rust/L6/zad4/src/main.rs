fn main() {}

fn comp(a: Vec<i64>, b: Vec<i64>) -> bool {
    let mut new_a: Vec<i64> = a.into_iter().map(|x| x*x).collect();
    let mut new_b = b;
    new_a.sort();
    new_b.sort();
    new_a == new_b
}

#[test]
fn test1() {
    let a1 = vec![121, 144, 19, 161, 19, 144, 19, 11];
    let a2 = vec![11*11, 121*121, 144*144, 19*19, 161*161, 19*19, 144*144, 19*19];
    assert_eq!(comp(a1, a2), true);
}

#[test]
fn test2() {
    let a1 = vec![121, 144, 19, 161, 19, 144, 19, 11];
    let a2 = vec![11*21, 121*121, 144*144, 19*19, 161*161, 19*19, 144*144, 19*19];
    assert_eq!(comp(a1, a2), false);
}

#[test]
fn test3() {
    let a1 = vec![121, 144, 19, 161, 19, 144, 19, 11];
    let a2 = vec![11*21, 121*121, 144*144, 19*19, 161*161, 19*19, 144*144, 19*19];
    assert_eq!(comp(a1, a2), false);
}

#[test]
fn test4() {
    let a1 = vec![19, 161];
    let a2 = vec![19*19, 161*161, 12*19];
    assert_eq!(comp(a1, a2), false);
}

#[test]
fn test5() {
    let a1 = vec![2, 2, 3];
    let a2 = vec![4, 9, 9];
    assert_eq!(comp(a1, a2), false);
}

#[test]
fn test6() {
    let a1 = vec![2, 4, 8];
    let a2 = vec![16, 64, 4];
    assert_eq!(comp(a1, a2), true);
}

#[test]
fn test7() {
    let a1 = vec![2, 3];
    let a2 = vec![4, 9];
    assert_eq!(comp(a1, a2), true);
}

#[test]
fn test8() {
    let a1 = vec![2, 3];
    let a2 = vec![16, 6, 9, 15, 19];
    assert_eq!(comp(a1, a2), false);
}

#[test]
fn test9() {
    let a1 = vec![2, 3];
    let a2 = vec![];
    assert_eq!(comp(a1, a2), false);
}

#[test]
fn test10() {
    let a1 = vec![-121, -144, 19, -161, 19, -144, 19, -11];
    let a2 = vec![121, 14641, 20736, 361, 25921, 361, 20736, 361];
    assert_eq!(comp(a1, a2), true);
}
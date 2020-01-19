fn main() {}

fn ann_and_john(n: i32, isAnn: bool) -> Vec<i32> {
    let mut ann: Vec<i32> = vec![1];
    let mut john: Vec<i32> = vec![0];
    for i in 1..n {
        john.push(i - ann[john[(i-1) as usize] as usize]);
        ann.push(i - john[ann[(i-1) as usize] as usize]);
    }
    if isAnn { ann } else { john }
}

fn john(n: i32) -> Vec<i32> {
    ann_and_john(n, false)
}

fn ann(n: i32) -> Vec<i32> {
    ann_and_john(n, true)
}

fn sum_john(n: i32) -> i32 {
    john(n).iter().sum()
}

fn sum_ann(n: i32) -> i32 {
    ann(n).iter().sum()
}

#[test]
fn test1() {
    assert_eq!(john(11), vec![0, 0, 1, 2, 2, 3, 4, 4, 5, 6, 6]);
}

#[test]
fn test2() {
    assert_eq!(sum_john(1), 0);
}

#[test]
fn test3() {
    assert_eq!(sum_ann(1), 1);
}

#[test]
fn test4() {
    assert_eq!(sum_ann(115), 4070);
}

#[test]
fn test5() {
    assert_eq!(sum_ann(150), 6930);
}

#[test]
fn test6() {
    assert_eq!(sum_john(78), 1861);
}

#[test]
fn test7() {
    assert_eq!(sum_john(75), 1720);
}

#[test]
fn test8() {
    assert_eq!(ann(15), vec![1, 1, 2, 2, 3, 3, 4, 5, 5, 6, 6, 7, 8, 8, 9]);
}

#[test]
fn test9() {
    assert_eq!(ann(6), vec![1, 1, 2, 2, 3, 3]);
}

#[test]
fn test10() {
    assert_eq!(john(14), vec![0, 0, 1, 2, 2, 3, 4, 4, 5, 6, 6, 7, 7, 8]);
}



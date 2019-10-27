fn main() {}

use std::collections::BTreeSet;

fn longest(a1: &str, a2: &str) -> String {
    let mut set = BTreeSet::new();
    a1.chars().for_each(|c| {set.insert(c);});
    a2.chars().for_each(|c| {set.insert(c);});
    set.into_iter().collect()
}

#[test]
fn test1() {
    assert_eq!(longest("aretheyhere", "yestheyarehere"), "aehrsty");
}

#[test]
fn test2() {
    assert_eq!(longest("loopingisfunbutdangerous", "lessdangerousthancoding"), "abcdefghilnoprstu")
}

#[test]
fn test3() {
    assert_eq!(longest("abc", "abc"), "abc")
}

#[test]
fn test4() {
    assert_eq!(longest("cba", "abc"), "abc")
}

#[test]
fn test5() {
    assert_eq!(longest("zxc", "abc"), "abcxz")
}

#[test]
fn test6() {
    assert_eq!(longest("lala", "pola"), "alop")
}

#[test]
fn test7() {
    assert_eq!(longest("man", "woman"), "amnow")
}

#[test]
fn test8() {
    assert_eq!(longest("aaa", "aaa"), "a")
}

#[test]
fn test9() {
    assert_eq!(longest("aaa", "bbb"), "ab")
}

#[test]
fn test10() {
    assert_eq!(longest("po", "pis"), "iops")
}
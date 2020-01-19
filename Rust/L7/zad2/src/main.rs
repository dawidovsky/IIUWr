use std::collections::BTreeMap;

fn main() {}

fn letter_frequency(input: &str) -> BTreeMap<char, i32> {
    let letters: String = input.to_lowercase().chars().filter(|c| c.is_alphabetic()).collect();
    let mut res: BTreeMap<char, i32> = BTreeMap::new();
    for c in letters.chars() {
        *res.entry(c).or_insert(0) += 1;
    }
    res
}

#[test]
fn test1() {
    let answer: BTreeMap<char, i32> =
        [('a', 2),
         ('c', 1),
         ('l', 1),
         ('t', 1),
         ('u', 1)]
         .iter().cloned().collect();

      assert_eq!(letter_frequency("actual"), answer);
}

#[test]
fn test2() {
    let answer: BTreeMap<char, i32> =
        [('a', 2),
         ('c', 1),
         ('l', 1),
         ('t', 1),
         ('u', 1)]
         .iter().cloned().collect();

      assert_eq!(letter_frequency("a1c t2u a3 l"), answer);
}

#[test]
fn test3() {
    let answer: BTreeMap<char, i32> =
        [('r', 2),
         ('t', 1)]
         .iter().cloned().collect();

      assert_eq!(letter_frequency("213  R  123 Tr"), answer);
}

#[test]
fn test4() {
    let answer: BTreeMap<char, i32> =
        [('a', 2),
         ('c', 1),
         ('l', 2),
         ('t', 1),
         ('u', 1)]
         .iter().cloned().collect();

      assert_eq!(letter_frequency("actuall"), answer);
}

#[test]
fn test5() {
    let answer: BTreeMap<char, i32> =
        [('m', 3)]
         .iter().cloned().collect();

      assert_eq!(letter_frequency("mmm"), answer);
}

#[test]
fn test6() {
    let answer: BTreeMap<char, i32> =
        [('a', 1)]
         .iter().cloned().collect();

      assert_eq!(letter_frequency("1a23"), answer);
}

#[test]
fn test7() {
    let answer: BTreeMap<char, i32> =
        [('a', 2),
         ('b', 1),
         ('c', 1)]
         .iter().cloned().collect();

      assert_eq!(letter_frequency("AbcA"), answer);
}

#[test]
fn test8() {
    let answer: BTreeMap<char, i32> =
        [('b', 1),
         ('e', 1)]
         .iter().cloned().collect();

      assert_eq!(letter_frequency("B123e"), answer);
}

#[test]
fn test9() {
    let answer: BTreeMap<char, i32> =
        [('a', 2),
         ('u', 1)]
         .iter().cloned().collect();

      assert_eq!(letter_frequency("A U A"), answer);
}

#[test]
fn test1() {
    let answer: BTreeMap<char, i32> =
        [('a', 1),
         ('d', 2),
         ('i', 1),
         ('w', 1)]
         .iter().cloned().collect();

      assert_eq!(letter_frequency("Dawid"), answer);
}

#[test]
fn test10() {
    let answer: BTreeMap<char, i32> =
        [('a', 3),
         ('b', 2),
         ('f', 1),
         ('p', 1),
         ('s', 1),
         ('t', 2),
         ('u', 1),
         ('x', 5)]
         .iter().cloned().collect();

      assert_eq!(letter_frequency("AaabBF UttsP xxxxx"), answer);
}
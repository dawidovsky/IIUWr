use std::iter::FromIterator;

fn main() {}

fn first_letter_uppercase(s: &str) -> String {
    let mut chars: Vec<char> = s.chars().collect::<Vec<char>>();
    chars[0].make_ascii_uppercase();
    String::from_iter(chars)
}

fn camel_case(str: &str) -> String {
    if str == "" { return "".to_string() }
    let splitted: Vec<&str> = str.split_whitespace().collect();
    let res: Vec<String> = splitted.iter().map(|s| first_letter_uppercase(s)).collect();
    res.join("")
}

#[test]
fn test1() {
  assert_eq!(camel_case("test case"), "TestCase");
}

#[test]
fn test2() {
    assert_eq!(camel_case("camel case method"), "CamelCaseMethod");
}

#[test]
fn test3() {
    assert_eq!(camel_case("say hello "), "SayHello");
}

#[test]
fn test4() {
    assert_eq!(camel_case(" camel case word"), "CamelCaseWord");
}

#[test]
fn test5() {
    assert_eq!(camel_case(""), "");
}

#[test]
fn test6() {
  assert_eq!(camel_case("inside something"), "InsideSomething");
}

#[test]
fn test7() {
    assert_eq!(camel_case("Vardy scores"), "VardyScores");
}

#[test]
fn test8() {
    assert_eq!(camel_case("goal goal goal"), "GoalGoalGoal");
}

#[test]
fn test9() {
    assert_eq!(camel_case("oh my god"), "OhMyGod");
}

#[test]
fn test10() {
    assert_eq!(camel_case("qwe"), "Qwe");
}
fn main() {alphabet_position("-=!@#$%^&*()_+[];,./{}:|<>? ");}

fn alphabet_position(text: &str) -> String {
    let new_text: String = text.chars().map(|c| c.to_lowercase().to_string()).collect();
    let filtered: String = new_text.chars().filter(|c| c.is_ascii_alphabetic()).collect();
    let mut res: String = filtered.chars().map(|c| ((c as u32).saturating_sub('a' as u32) + 1).to_string() + " ").collect();
    res.truncate(res.len().saturating_sub(1));
    res
}

#[test]
fn test1() {
    assert_eq!(
        alphabet_position("The sunset sets at twelve o' clock."),
        "20 8 5 19 21 14 19 5 20 19 5 20 19 1 20 20 23 5 12 22 5 15 3 12 15 3 11".to_string()
    );
}

#[test]
fn test2() {
    assert_eq!(
        alphabet_position("The"),
        "20 8 5".to_string()
    );
}

#[test]
fn test3() {
    assert_eq!(
        alphabet_position("-=!@#$%^&*()_+[];,./{}:|<>? "),
        "".to_string()
    );
}

#[test]
fn test4() {
    assert_eq!(
        alphabet_position("aaa"),
        "1 1 1".to_string()
    );
}

#[test]
fn test5() {
    assert_eq!(
        alphabet_position("a b c"),
        "1 2 3".to_string()
    );
}

#[test]
fn test6() {
    assert_eq!(
        alphabet_position("z"),
        "26".to_string()
    );
}

#[test]
fn test7() {
    assert_eq!(
        alphabet_position("w"),
        "23".to_string()
    );
}

#[test]
fn test8() {
    assert_eq!(
        alphabet_position("c 123cc"),
        "3 3 3".to_string()
    );
}

#[test]
fn test9() {
    assert_eq!(
        alphabet_position("d"),
        "4".to_string()
    );
}

#[test]
fn test10() {
    assert_eq!(
        alphabet_position("a"),
        "1".to_string()
    );
}
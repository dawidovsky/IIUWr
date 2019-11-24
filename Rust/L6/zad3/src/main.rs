fn main() {
    println!("{}", print(7).unwrap());
}

fn triangle(n : i32, upper: bool) -> String {
    let mut res = "".to_string();
    let upper_dir: Vec<i32> = (0..n/2 + 1).collect();
    let lower_dir: Vec<i32> = (0..n/2).rev().collect();
    let direction = if upper { upper_dir } else { lower_dir };
    for i in direction {
        for _ in 0..(n-2*i)/2 {
            res.push(' ');
        }
        for _ in 0..2 * i + 1 {
            res.push('*');
        }
        res.push('\n');
    }
    res
}

fn print(n: i32) -> Option<String> {
    if n % 2 == 0 || n < 1 { return None }
    let mut res = "".to_string();
    res.push_str(&triangle(n, true));
    res.push_str(&triangle(n, false));
    Some(res)
}

#[test]
fn test1() {
    assert_eq!(print(3), Some(" *\n***\n *\n".to_string()) );
}

#[test]
fn test2() {
    assert_eq!(print(-3),None);
}

#[test]
fn test3() {
    assert_eq!(print(2),None);
}

#[test]
fn test4() {
    assert_eq!(print(0),None);
}

#[test]
fn test5() {
    assert_eq!(print(1), Some("*\n".to_string()) );
}

#[test]
fn test6() {
    assert_eq!(print(1), Some("*\n".to_string()) );
}

#[test]
fn test7() {
    assert_eq!(print(-123), None);
}

#[test]
fn test8() {
    assert_eq!(print(-32), None);
}

#[test]
fn test9() {
    assert_eq!(print(24), None);
}

#[test]
fn test10() {
    assert_eq!(print(2000), None);
}
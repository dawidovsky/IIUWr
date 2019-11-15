fn main() {}

pub fn highlight(code: &str) -> String {
    let mut res = "".to_string();
    let mut tmp = "".to_string();
    let splitted: Vec<char> = code.split("").filter_map(|c| c.parse::<char>().ok()).collect();
    let mut last_char = if splitted.len() > 0 { splitted[0] } else {'c'};
    for c in splitted {
        if c == last_char || (c.is_numeric() && last_char.is_numeric()) { tmp.push(c) }
        else {
            println!("{}", tmp);
            res.push_str(&choose_highlight(&tmp));
            last_char = c;
            tmp = "".to_string();
            tmp.push(c);
        }
    }
    res.push_str(&choose_highlight(&tmp));
    res
}

fn make_highlight(string: &str, color: &str) -> String {
    format!("<span style=\"color: {}\">{}</span>", color, string)
}

fn choose_highlight(string: &str) -> String {
    if string.contains('F') { return make_highlight(&string, "pink") }
    if string.contains('L') { return make_highlight(&string, "red") }
    if string.contains('R') { return make_highlight(&string, "green") }
    if string.parse::<u64>().is_ok() { return make_highlight(&string, "orange") }
    return string.to_string()
}

#[test]
fn test1() {
    assert_eq!(highlight("F3RF5LF7"), r#"<span style="color: pink">F</span><span style="color: orange">3</span><span style="color: green">R</span><span style="color: pink">F</span><span style="color: orange">5</span><span style="color: red">L</span><span style="color: pink">F</span><span style="color: orange">7</span>"#);
}

#[test]
fn test2() {
    assert_eq!(highlight("FF"), r#"<span style="color: pink">FF</span>"#);
}

#[test]
fn test3() {
    assert_eq!(highlight("FFFR345F2LL"), r#"<span style="color: pink">FFF</span><span style="color: green">R</span><span style="color: orange">345</span><span style="color: pink">F</span><span style="color: orange">2</span><span style="color: red">LL</span>"#);
}

#[test]
fn test4() {
    assert_eq!(highlight("FR"), r#"<span style="color: pink">F</span><span style="color: green">R</span>"#);
}

#[test]
fn test5() {
    assert_eq!(highlight("()"), r#"()"#);
}

#[test]
fn test6() {
    assert_eq!(highlight("F(F)R"), r#"<span style="color: pink">F</span>(<span style="color: pink">F</span>)<span style="color: green">R</span>"#);
}

#[test]
fn test7() {
    assert_eq!(highlight("(23)"), r#"(<span style="color: orange">23</span>)"#);
}

#[test]
fn test8() {
    assert_eq!(highlight("(1R22502566372)R"), r#"(<span style="color: orange">1</span><span style="color: green">R</span><span style="color: orange">22502566372</span>)<span style="color: green">R</span>"#);
}

#[test]
fn test9() {
    assert_eq!(highlight(""), r#""#);
}

#[test]
fn test10() {
    assert_eq!(highlight("2(1)2"), r#"<span style="color: orange">2</span>(<span style="color: orange">1</span>)<span style="color: orange">2</span>"#);
}
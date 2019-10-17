fn main() {}

fn printer_error(s: &str) -> String {
    let some: Vec<&str> = s.split(|c| c > 'm').collect();
    format!("{}/{}", some.len()-1, s.to_string().len())
}

#[test]
fn test1() {
    assert_eq!(&printer_error("aaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbmmmmmmmmmmmmmmmmmmmxyz"), "3/56");
}

#[test]
fn test2() {
    assert_eq!(&printer_error("kkkwwwaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbmmmmmmmmmmmmmmmmmmmxyz"), "6/60");
}

#[test]
fn test3() {
    assert_eq!(&printer_error("kkkwwwaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbmmmmmmmmmmmmmmmmmmmxyzuuuuu"), "11/65");
}

#[test]
fn test4() {
    assert_eq!(&printer_error("abc"), "0/3");
}

#[test]
fn test5() {
    assert_eq!(&printer_error("abcxyz"), "3/6");
}
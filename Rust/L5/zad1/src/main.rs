fn main() {}

fn xo(string: &'static str) -> bool {
    let xcount: String = string.chars().filter(|c| *c == 'x' || *c == 'X').collect();
    let ocount: String = string.chars().filter(|c| *c == 'o' || *c == 'O').collect();
    xcount.len() == ocount.len()
}

#[test]
fn test1(){
    assert_eq!(xo("xxoo"), true);
}

#[test]
fn test2(){
    assert_eq!(xo(""), true);
}

#[test]
fn test3(){
    assert_eq!(xo("xxooo"), false);
}

#[test]
fn test4(){
    assert_eq!(xo("xxqweoo"), true);
}

#[test]
fn test5(){
    assert_eq!(xo("Xo"), true);
}

#[test]
fn test6(){
    assert_eq!(xo("xxOo"), true);
}

#[test]
fn test7(){
    assert_eq!(xo("xxxm"), false);
}

#[test]
fn test8(){
    assert_eq!(xo("Oo"), false);
}

#[test]
fn test9(){
    assert_eq!(xo("OoXx"), true);
}

#[test]
fn test10(){
    assert_eq!(xo("ooom"), false);
}
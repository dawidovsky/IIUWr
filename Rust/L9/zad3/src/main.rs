fn main() {}

fn order(sentence: &str) -> String {
    if sentence == "" { return "".to_string() }
    let strings: Vec<&str> = sentence.split(" ").collect();
    let mut res: Vec<String> = vec![];
    let mut iter: u8 = 1;
    for _ in 1..10 {
        for s in &strings {
            if s.chars().collect::<Vec<char>>().contains(&((iter + '0' as u8) as char)) {
                res.push(s.to_string());
                iter += 1;
                break;
            }
        }
    }
    res.join(" ")
}

#[test]
fn test1(){
    assert_eq!(order("is1 Thi2s T4est 3a"), "is1 Thi2s 3a T4est");
}

#[test]
fn test2(){
    assert_eq!(order("is2 Thi1s T4est 3a"), "Thi1s is2 3a T4est");
}

#[test]
fn test3(){
    assert_eq!(order("is2 som1e"), "som1e is2");
}

#[test]
fn test4(){
    assert_eq!(order("is1 2a"), "is1 2a");
}

#[test]
fn test5(){
    assert_eq!(order("n2ow is1 o3k"), "is1 n2ow o3k");
}

#[test]
fn test6(){
    assert_eq!(order("4 2 3 1"), "1 2 3 4");
}

#[test]
fn test7(){
    assert_eq!(order("1 2 3 4"), "1 2 3 4");
}

#[test]
fn test8(){
    assert_eq!(order("why1"), "why1");
}

#[test]
fn test9(){
    assert_eq!(order("is1 some3 wron2g"), "is1 wron2g some3");
}

#[test]
fn test10(){
    assert_eq!(order(""), "");
}
fn main() {}

fn number_to_vec(n: u32) -> Vec<u32> {
    n.to_string().chars().map(|c| c.to_digit(10).unwrap()).collect()
}

fn encode(msg: String, n: i32) -> Vec<i32> {
    let mut res: Vec<i32> = Vec::new();
    let mut index: usize = 0;
    let values = number_to_vec(n as u32);
    for c in msg.chars() {
        res.push((c as u32 - 'a' as u32 + 1 + values[index]) as i32);
        if index == values.len() - 1 { index = 0; } else { index += 1; }
    }
    res
}

#[test]
fn test1(){
    assert_eq!(encode("scout".to_string(), 1939), vec![20, 12, 18, 30, 21]);
}

#[test]
fn test2(){
    assert_eq!(encode("scout".to_string(), 1939), vec![20, 12, 18, 30, 21]);
}

#[test]
fn test3(){
    assert_eq!(encode("scout".to_string(), 1939), vec![20, 12, 18, 30, 21]);
}

#[test]
fn test4(){
    assert_eq!(encode("scout".to_string(), 1939), vec![20, 12, 18, 30, 21]);
}

#[test]
fn test5(){
    assert_eq!(encode("scout".to_string(), 1939), vec![20, 12, 18, 30, 21]);
}

#[test]
fn test6(){
    assert_eq!(encode("scout".to_string(), 1939), vec![20, 12, 18, 30, 21]);
}

#[test]
fn test7(){
    assert_eq!(encode("scout".to_string(), 1939), vec![20, 12, 18, 30, 21]);
}

#[test]
fn test8(){
    assert_eq!(encode("scout".to_string(), 1939), vec![20, 12, 18, 30, 21]);
}

#[test]
fn test9(){
    assert_eq!(encode("scout".to_string(), 1939), vec![20, 12, 18, 30, 21]);
}

#[test]
fn test10(){
    assert_eq!(encode("scout".to_string(), 1939), vec![20, 12, 18, 30, 21]);
}

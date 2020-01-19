fn main() {
    dec2_fact_string(36288000);
}

fn dec2_fact_string(nb: u64) -> String {
    let mut iter: u64 = 1;
    let mut number: u64 = nb;
    let mut res: String = "".to_string();
    while number/iter != 0 {
        let value_to_insert = if number%iter < 10 { ((number%iter) as u8 + '0' as u8) as char } else {
            ((number%iter) as u8 + '7' as u8)  as char
        };
        res.push(value_to_insert);
        number /= iter;
        iter += 1;
    }
    let value_to_insert = if number%iter < 10 { ((number%iter) as u8 + '0' as u8) as char } else {
        ((number%iter) as u8 + '7' as u8)  as char
    };
    res.push(value_to_insert);
    res.chars().rev().collect()
}

fn fact_string_2dec(s: String) -> u64 {
    let mut fact = 1;
    let mut iter = 0;
    let mut res = 0;
    let rev_string: Vec<u64> = s.chars().map(|c| c as u64 - '0' as u64).rev().collect();
    let mut decoded_string: Vec<u64> = vec![];
    for val in rev_string.iter() {
        if val > &9 { decoded_string.push(*val - 7) } else { decoded_string.push(*val) }
    }
    for _ in 0..decoded_string.len() {
        res += fact * decoded_string[iter];
        iter += 1;
        fact *= iter as u64;
    }
    res
}


#[test]
fn test1(){
    assert_eq!(dec2_fact_string(2982), "4041000".to_string());
}

#[test]
fn test2(){
    assert_eq!(dec2_fact_string(463), "341010".to_string());
}

#[test]
fn test3(){
    assert_eq!(dec2_fact_string(36288000), "A0000000000".to_string());
}

#[test]
fn test4(){
    assert_eq!(dec2_fact_string(1), "10".to_string());
}

#[test]
fn test5(){
    assert_eq!(dec2_fact_string(2), "100".to_string());
}

#[test]
fn test6(){
    assert_eq!(fact_string_2dec("4041000".to_string()), 2982);
}

#[test]
fn test7(){
    assert_eq!(fact_string_2dec("27A0533231100".to_string()), 1273928000);
}


#[test]
fn test8(){
    assert_eq!(fact_string_2dec("0".to_string()), 0);
}


#[test]
fn test9(){
    assert_eq!(fact_string_2dec("10".to_string()), 1);
}

#[test]
fn test10(){
    assert_eq!(fact_string_2dec("100".to_string()), 2);
}

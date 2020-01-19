fn main() {}

fn power(a: u64, b: u64) -> u64 {
    a.pow(b as u32)
}

fn last_digit(lst: &[u64]) -> u64 {
    if lst.len() == 0 { return 1 }
    let mut help_vec: Vec<u64> = lst.to_vec();
    help_vec.iter().rev().fold(1, |accumulator, value|
                            power( if value < &20 { *value } else { value % 20 + 20 },
                                   if accumulator < 4 { accumulator } else { accumulator % 4 + 4 })) % 10
}

#[test]
fn test1(){
    assert_eq!(last_digit(&vec![]), 1);
}

#[test]
fn test2(){
    assert_eq!(last_digit(&vec![1, 2]), 1);
}

#[test]
fn test3(){
    assert_eq!(last_digit(&vec![3, 4, 5]), 1);
}

#[test]
fn test4(){
    assert_eq!(last_digit(&vec![4, 3, 6]), 4);
}

#[test]
fn test5(){
    assert_eq!(last_digit(&vec![7, 6, 21]), 1);
}

#[test]
fn test6(){
    assert_eq!(last_digit(&vec![12, 30, 21]), 6);
}

#[test]
fn test7(){
    assert_eq!(last_digit(&vec![2, 2, 2, 0]), 4);
}

#[test]
fn test8(){
    assert_eq!(last_digit(&vec![937640, 767456, 981242]), 0);
}

#[test]
fn test9(){
    assert_eq!(last_digit(&vec![123232, 694022, 140249]), 6);
}

#[test]
fn test10(){
    assert_eq!(last_digit(&vec![499942, 898102, 846073]), 6);
}

fn main() {}

fn dont_give_me_five(start: isize, end: isize) -> isize {
    let vec: Vec<String> = (start..end+1).map(|v| v.to_string()).collect();
    vec.iter().filter(|s| !s.contains("5")).count() as isize
}

#[test]
fn test1(){
    assert_eq!(dont_give_me_five(1, 9), 8);
}

#[test]
fn test2(){
    assert_eq!(dont_give_me_five(4, 17), 12);
}

#[test]
fn test3(){
    assert_eq!(dont_give_me_five(1, 4), 4);
}

#[test]
fn test4(){
    assert_eq!(dont_give_me_five(1, 5), 4);
}

#[test]
fn test5(){
    assert_eq!(dont_give_me_five(1, 6), 5);
}

#[test]
fn test6(){
    assert_eq!(dont_give_me_five(4, 5), 1);
}

#[test]
fn test7(){
    assert_eq!(dont_give_me_five(5, 5), 0);
}

#[test]
fn test8(){
    assert_eq!(dont_give_me_five(6, 7), 2);
}

#[test]
fn test9(){
    assert_eq!(dont_give_me_five(1, 3), 3);
}

#[test]
fn test10(){
    assert_eq!(dont_give_me_five(1, 2), 2);
}
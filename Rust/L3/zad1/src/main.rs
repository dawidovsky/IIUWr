fn main() {}

fn row_sum_odd_numbers(n:i64) -> i64 {
    n.pow(3)
}

#[test]
fn test1() {
  assert_eq!(row_sum_odd_numbers(1), 1);
}


#[test]
fn test2() {
  assert_eq!(row_sum_odd_numbers(2), 8);
}


#[test]
fn test3() {
  assert_eq!(row_sum_odd_numbers(3), 27);
}

#[test]
fn test4() {
  assert_eq!(row_sum_odd_numbers(42), 74088);
}

#[test]
fn test5() {
  assert_eq!(row_sum_odd_numbers(4), 64);
}


#[test]
fn test6() {
  assert_eq!(row_sum_odd_numbers(5), 125);
}


#[test]
fn test7() {
  assert_eq!(row_sum_odd_numbers(6), 216);
}

#[test]
fn test8() {
  assert_eq!(row_sum_odd_numbers(7), 343);
}

#[test]
fn test9() {
  assert_eq!(row_sum_odd_numbers(8), 512);
}

#[test]
fn test10() {
  assert_eq!(row_sum_odd_numbers(9), 729);
}
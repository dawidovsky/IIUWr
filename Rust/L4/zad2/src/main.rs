fn main() {}

fn even_numbers(array: &Vec<i32>, number: usize) -> Vec<i32> {
    let mut new_array: Vec<i32> = vec![];
    new_array.extend(array.iter().filter(|x| *x % 2 == 0).rev());
    new_array.get(..number).unwrap().to_vec().iter().rev().cloned().collect()
}

#[test]
fn test1() {
  assert_eq!(even_numbers(&vec!(1, 2, 3, 4, 5, 6, 7, 8, 9), 3), vec!(4, 6, 8));
}

#[test]
fn test2() {
  assert_eq!(even_numbers(&vec!(-22, 5, 3, 11, 26, -6, -7, -8, -9, -8, 26), 2), vec!(-8, 26));
}

#[test]
fn test3() {
  assert_eq!(even_numbers(&vec!(6, -25, 3, 7, 5, 5, 7, -3, 23), 1), vec!(6));
}

#[test]
fn test4() {
  assert_eq!(even_numbers(&vec!(1, 3, 5, 7, 2, 4), 2), vec!(2, 4));
}

#[test]
fn test5() {
  assert_eq!(even_numbers(&vec!(1, 2, 5, 7, 2, 4), 2), vec!(2, 4));
}

#[test]
fn test6() {
  assert_eq!(even_numbers(&vec!(1, 3, 5, 2, 2, 2), 2), vec!(2, 2));
}

#[test]
fn test7() {
  assert_eq!(even_numbers(&vec!(2, 4, 6), 2), vec!(4, 6));
}

#[test]
fn test8() {
  assert_eq!(even_numbers(&vec!(1, 3, 5, 7, 2, 4), 2), vec!(2, 4));
}

#[test]
fn test9() {
  assert_eq!(even_numbers(&vec!(8, 8), 2), vec!(8, 8));
}

#[test]
fn test10() {
  assert_eq!(even_numbers(&vec!(4, 4, 4, 2, 2, 4), 2), vec!(2, 4));
}

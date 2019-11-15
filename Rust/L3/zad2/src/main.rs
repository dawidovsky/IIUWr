fn main() {}

fn number(bus_stops:&[(i32,i32)]) -> i32 {
    let mut sum = 0;
    bus_stops.iter().for_each(|x| sum += x.0 - x.1);
    sum
}

#[test]
fn test1() {
  assert_eq!(number(&[(10,0),(3,5),(5,8)]), 5);
}

#[test]
fn test2() {
  assert_eq!(number(&[(3,0),(9,1),(4,10),(12,2),(6,1),(7,10)]), 17);
}

#[test]
fn test3() {
  assert_eq!(number(&[(3,0)]), 3);
}

#[test]
fn test4() {
  assert_eq!(number(&[(3,0),(9,1)]), 11);
}

#[test]
fn test5() {
  assert_eq!(number(&[(10,0),(0,9)]), 1);
}

#[test]
fn test6() {
  assert_eq!(number(&[(10,0),(0,10)]), 0);
}

#[test]
fn test7() {
  assert_eq!(number(&[(3,0),(2,0)]), 5);
}

#[test]
fn test8() {
  assert_eq!(number(&[(4,0),(2,2),(6,6),(7,7)]), 4);
}

#[test]
fn test9() {
  assert_eq!(number(&[(100,0),(25, 100)]), 25);
}

#[test]
fn test10() {
  assert_eq!(number(&[(5,0),(10,0)]), 15);
}
fn main() {}

fn count_red_beads(n: u32) -> u32 {
    if n == 0 { 0 } else { 2 * n - 2 }
}

#[test]
fn test1() {
    assert_eq!(count_red_beads(0), 0)
}

#[test]
fn test2() {
    assert_eq!(count_red_beads(1), 0)
}

#[test]
fn test3() {
    assert_eq!(count_red_beads(3), 4)
}

#[test]
fn test4() {
    assert_eq!(count_red_beads(5), 8);
}

#[test]
fn test5() {
    assert_eq!(count_red_beads(6), 10)
}
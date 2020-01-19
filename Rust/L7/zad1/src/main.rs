fn main() {}

fn chessboard_cell_color(cell1: &str, cell2: &str) -> bool {
    let value1: u32 = cell1.chars().map(|x| x as u32).sum();
    let value2: u32 = cell2.chars().map(|x| x as u32).sum();
    value1 % 2 == value2 % 2
}

#[test]
fn test1(){
    assert_eq!(chessboard_cell_color("A1", "C3"), true);
}

#[test]
fn test2(){
    assert_eq!(chessboard_cell_color("A1", "H3"), false);
}

#[test]
fn test3(){
    assert_eq!(chessboard_cell_color("A1", "A2"), false);
}

#[test]
fn test4(){
    assert_eq!(chessboard_cell_color("A1", "C1"), true);
}

#[test]
fn test5(){
    assert_eq!(chessboard_cell_color("A1", "A1"), true);
}

#[test]
fn test6(){
    assert_eq!(chessboard_cell_color("A1", "G3"), true);
}

#[test]
fn test7(){
    assert_eq!(chessboard_cell_color("A3", "H3"), false);
}

#[test]
fn test8(){
    assert_eq!(chessboard_cell_color("A1", "A2"), false);
}

#[test]
fn test9(){
    assert_eq!(chessboard_cell_color("B1", "C3"), false);
}

#[test]
fn test10(){
    assert_eq!(chessboard_cell_color("D1", "B3"), true);
}

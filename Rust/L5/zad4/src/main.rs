fn main() {
    execute("LFFFFFRFFFRFFFRFFFFFFF ");
}

pub fn execute(code: &str) -> String {
    if code == "" { return "*".to_string() }
    let mut direction: u8 = 1; // 0 - N, 1 - E, 2 - S, 3 - W;
    let mut vertical_level_max: i64 = 0;
    let mut vertical_level_min: i64 = 0;
    let mut horizontal_level_max: i64 = 0;
    let mut horizontal_level_min: i64 = 0;
    let mut ver_lvl: i64 = 0;
    let mut hor_lvl: i64 = 0;
    for c in code.chars() {
        match c {
            'R' => iter_dir(&mut direction, '+'),
            'L' => iter_dir(&mut direction, '-'),
            _ => match direction {
                0 => ver_lvl += 1,
                1 => hor_lvl += 1,
                2 => ver_lvl -= 1,
                3 => hor_lvl -= 1,
                _ => ()
            }
        }
        if ver_lvl > vertical_level_max { vertical_level_max = ver_lvl; }
        if ver_lvl < vertical_level_min { vertical_level_min = ver_lvl; }
        if hor_lvl > horizontal_level_max { horizontal_level_max = hor_lvl; }
        if hor_lvl < horizontal_level_min { horizontal_level_min = hor_lvl; }
    }
    let mut grid: Vec<Vec<char>> = vec![vec![' '; (horizontal_level_max - horizontal_level_min + 1) as usize];
                                                  (vertical_level_max - vertical_level_min + 1) as usize];
    print!("{} {} {} {}", vertical_level_max, vertical_level_min, horizontal_level_max, horizontal_level_min);
    "".to_string()
}

fn iter_dir(i: &mut u8, c: char) -> () {
    if c == '+'{
        if *i == 3 { *i = 0; } else { *i += 1; }
    }
    else {
        if *i == 0 { *i = 3; } else { *i -= 1; }
    }
}

#[test]
fn test1(){
    assert_eq!(execute(""), "*");
}

#[test]
fn test2() {
    assert_eq!(execute("FFFFF"), "******");
}

#[test]
fn test3() {
    assert_eq!(
        execute("FFFFFLFFFFFLFFFFFLFFFFFL"),
        "******\r\n*    *\r\n*    *\r\n*    *\r\n*    *\r\n******",
     );
}

#[test]
fn test4() {
    assert_eq!(
        execute("LFFFFFRFFFRFFFRFFFFFFF"),
        "    ****\r\n    *  *\r\n    *  *\r\n********\r\n    *   \r\n    *   ",
    );
}

#[test]
fn test5() {
    assert_eq!(
        execute("LF5RF3RF3RF7"),
        "    ****\r\n    *  *\r\n    *  *\r\n********\r\n    *   \r\n    *   ",
    );
}

#[test]
fn test6() {
    assert_eq!(execute("FF"), "**");
}

#[test]
fn test7() {
    assert_eq!(execute("FFF"), "***");
}

#[test]
fn test8() {
    assert_eq!(execute("F6"), "*******");
}

#[test]
fn test9() {
    assert_eq!(execute("F7"), "********");
}

#[test]
fn test10() {
    assert_eq!(execute("F8"), "*********");
}
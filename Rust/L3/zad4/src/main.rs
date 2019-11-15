fn main() {}

fn zoom(n: i32) -> String {
    let mut results: Vec<Vec<char>> = vec![vec!['x'; n as usize]; n as usize];
    if n == 1 {
        return "■".to_string()
    }
    else {
        gen_zoom_effect(is_black(n), 0, n as usize, &mut results);
    }
    let mut res: String = "".to_string();
    for val in results.iter() {
        res.push_str(&val.iter().collect::<String>());
        res.push('\n');
    }
    res.pop();
    res
}

fn gen_zoom_effect(is_black: bool, starting_point: usize,
                   n: usize, res: &mut Vec<Vec<char>>) -> (){
    let white: char = '■';
    let black: char = '□';
    if starting_point == n/2{
        res[starting_point][starting_point] = if is_black { black } else { white };
    }
    else {
        for i in starting_point..n-starting_point { res[starting_point][i] = if is_black { black } else { white };}
        for i in starting_point..n-starting_point { res[i][starting_point] = if is_black { black } else { white };}
        for i in starting_point..n-starting_point { res[n-starting_point-1][i] = if is_black { black } else { white };}
        for i in starting_point..n-starting_point { res[i][n-starting_point-1] = if is_black { black } else { white };}
        gen_zoom_effect(!is_black, starting_point + 1, n, res);
    }
}

fn is_black(n :i32) -> bool {
    let mut vec: Vec<i32> = vec![];
    for i in 0..n {
        vec.push(3 + i*4)
    }
    vec.contains(&n)
}


#[test]
fn test1(){
    assert_eq!(zoom(1), "■");
}

#[test]
fn test2() {
    assert_eq!(zoom(3), "\
□□□
□■□
□□□"
  );
}

#[test]
fn test_3() {
    assert_eq!(zoom(5), "\
■■■■■
■□□□■
■□■□■
■□□□■
■■■■■"
  );
}

#[test]
fn test_4() {
    assert_eq!(zoom(7), "\
□□□□□□□
□■■■■■□
□■□□□■□
□■□■□■□
□■□□□■□
□■■■■■□
□□□□□□□"
  );
}

#[test]
fn test_5() {
    assert_eq!(zoom(9), "\
■■■■■■■■■
■□□□□□□□■
■□■■■■■□■
■□■□□□■□■
■□■□■□■□■
■□■□□□■□■
■□■■■■■□■
■□□□□□□□■
■■■■■■■■■"
  );
}
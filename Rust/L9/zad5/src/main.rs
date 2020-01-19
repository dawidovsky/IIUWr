fn main() {}

mod solution {

    fn push_elems(prev: i32, diff: i32, res: &mut Vec<String>) -> () {
        if diff == 1 {
            res.push(prev.to_string());
        }
        else if diff == 2 {
            res.push(prev.to_string());
            res.push((prev + 1).to_string());
        }
        else {
            res.push(prev.to_string() + "-" + &(prev + diff - 1).to_string());
        }
    }

    pub fn range_extraction(a: &[i32]) -> String {
        let mut res: Vec<String> = vec![];
        let mut prev = a[0];
        let mut diff = 1;
        for i in 1..a.len() {
            if prev + diff == a[i] {
                diff += 1;
            }
            else {
                push_elems(prev, diff, &mut res);
                diff = 1;
                prev = a[i];
            }
        }
        push_elems(prev, diff, &mut res);
        res.join(",")
    }
}

#[test]
fn test1() {
    assert_eq!("-6,-3-1,3-5,7-11,14,15,17-20", solution::range_extraction(&[-6,-3,-2,-1,0,1,3,4,5,7,8,9,10,11,14,15,17,18,19,20]));	
}

#[test]
fn test2() {
    assert_eq!("-3--1,2,10,15,16,18-20", solution::range_extraction(&[-3,-2,-1,2,10,15,16,18,19,20]));
}

#[test]
fn test3() {
    assert_eq!("1-5", solution::range_extraction(&[1,2,3,4,5]));
}

#[test]
fn test4() {
    assert_eq!("1-5,7", solution::range_extraction(&[1,2,3,4,5,7]));
}

#[test]
fn test5() {
    assert_eq!("-5-5", solution::range_extraction(&[-5,-4,-3,-2,-1,0,1,2,3,4,5]));
}

#[test]
fn test6() {
    assert_eq!("1,2", solution::range_extraction(&[1,2]));
}

#[test]
fn test7() {
    assert_eq!("1-3", solution::range_extraction(&[1,2,3]));
}

#[test]
fn test8() {
    assert_eq!("1,2,4-6,8", solution::range_extraction(&[1,2,4,5,6,8]));
}

#[test]
fn test9() {
    assert_eq!("1,2,4,5", solution::range_extraction(&[1,2,4,5]));
}

#[test]
fn test10() {
    assert_eq!("1-5,7-9", solution::range_extraction(&[1,2,3,4,5,7,8,9]));
}
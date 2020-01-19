fn main() {}

fn part_list(arr: Vec<&str>) -> String {
    let mut res = "".to_string();
    let mut tmp_res: Vec<String> = vec![];
    for i in 1..arr.len() {
        for j in 0..i {
            tmp_res.push(arr[j].to_string());
        }
        res.push('(');
        res.push_str(&tmp_res.join(" "));
        res.push_str(", ");
        tmp_res.clear();
        for j in i..arr.len() {
            tmp_res.push(arr[j].to_string());
        }
        res.push_str(&tmp_res.join(" "));
        res.push(')');
        tmp_res.clear();
    }
    res
}

#[test]
fn test1(){
    assert_eq!(part_list(vec!["some", "thing"]), "(some, thing)");
}

#[test]
fn test2(){
    assert_eq!(part_list(vec!["I", "wish", "I", "hadn't", "come"]), "(I, wish I hadn't come)(I wish, I hadn't come)(I wish I, hadn't come)(I wish I hadn't, come)");
}

#[test]
fn test3(){
    assert_eq!(part_list(vec!["cdIw", "tzIy", "xDu", "rThG"]), "(cdIw, tzIy xDu rThG)(cdIw tzIy, xDu rThG)(cdIw tzIy xDu, rThG)");
}

#[test]
fn test4(){
    assert_eq!(part_list(vec!["qwe", "asd"]), "(qwe, asd)");
}

#[test]
fn test5(){
    assert_eq!(part_list(vec!["asd", "qwe"]), "(asd, qwe)");
}

#[test]
fn test6(){
    assert_eq!(part_list(vec!["12o31", "12o31"]), "(12o31, 12o31)");
}

#[test]
fn test7(){
    assert_eq!(part_list(vec!["x", "z"]), "(x, z)");
}

#[test]
fn test8(){
    assert_eq!(part_list(vec!["c", "z"]), "(c, z)");
}

#[test]
fn test9(){
    assert_eq!(part_list(vec!["a", "s"]), "(a, s)");
}

#[test]
fn test10(){
    assert_eq!(part_list(vec!["some", "thing", "use"]), "(some, thing use)(some thing, use)");
}

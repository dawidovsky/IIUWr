fn main() {}

fn next_bigger_number(n: i64) -> i64 {
    let num_str = n.to_string();
    let chr: Vec<char> = num_str.chars().collect();
    let num = chr[chr.len() - 1];
}

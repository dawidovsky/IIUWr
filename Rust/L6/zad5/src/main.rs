fn main() {}

struct Sudoku{
    data: Vec<Vec<u32>>,
}

fn check_col_row(sud: Vec<Vec<u32>>, index: i64, is_row: bool) -> bool {
	let mut res: Vec<u32> = Vec::new();
	for i in 0..sud.len() {
		let value = if is_row { sud[index as usize][i] } else { sud[i][index as usize] };
		if res.contains(&value) { return false }
		else { res.push(value); }
	}
	return true
}

fn check_box(sud: Vec<Vec<u32>>, row_index: i64, col_index: i64, box_size: i64) -> bool {
	let mut res: Vec<u32> = Vec::new();
	for i in 0..box_size {
		for j in 0..box_size {
			let value = sud[(i + row_index) as usize][(j + col_index) as usize];
			if res.contains(&value) { return false }
			else { res.push(value); }
		}
	}
	return true
}

fn is_valid(sudoku: &Vec<Vec<u32>>, row: i64, col: i64, box_size: i64) -> bool {
	return check_col_row(sudoku.to_vec(), row, true) && check_col_row(sudoku.to_vec(), col, false) &&
		   check_box(sudoku.to_vec(), row - row % box_size, col - col % box_size, box_size as i64)
}

fn check_values_and_length(sud: &Vec<Vec<u32>>) -> bool {
	let max_row_value = sud.len() as u32;
	for row in sud {
		for value in row {
			if value > &max_row_value || value < &1 { return false }
		}
	}
	for row in sud {
		if row.len() != max_row_value as usize { return false }
	}
	return true
}

impl Sudoku{
	fn is_valid(&self) -> bool {
		if !check_values_and_length(&self.data) { return false }
		let box_size = (self.data.len() as f64).sqrt() as i64;
		for i in 0..self.data.len() {
			for j in 0..self.data.len() {
				if !is_valid(&self.data, i as i64, j as i64, box_size) { return false }
			}
		}
		true
	}
}

#[test]
fn test1() {
	let good_sudoku = Sudoku{
        data: vec![
                vec![7,8,4, 1,5,9, 3,2,6],
                vec![5,3,9, 6,7,2, 8,4,1],
                vec![6,1,2, 4,3,8, 7,5,9],

                vec![9,2,8, 7,1,5, 4,6,3],
                vec![3,5,7, 8,4,6, 1,9,2],
                vec![4,6,1, 9,2,3, 5,8,7],

                vec![8,7,6, 3,9,4, 2,1,5],
                vec![2,4,3, 5,6,1, 9,7,8],
                vec![1,9,5, 2,8,7, 6,3,4]
            ]
    };
	assert_eq!(good_sudoku.is_valid(), true);
}

#[test]
fn test2() {
	let good_sudoku = Sudoku{
        data: vec![
                vec![1, 4,  2, 3],
                vec![3, 2,  4, 1],

                vec![4, 1,  3, 2],
                vec![2, 3,  1, 4],
            ]
    };
	assert_eq!(good_sudoku.is_valid(), true);
}

#[test]
fn test3() {
	let good_sudoku = Sudoku{
        data: vec![
                vec![1, 4,  2, 3],
                vec![3, 2,  4, 1],

                vec![4, 1,  3, 2],
                vec![2, 1, 4],
            ]
    };
	assert_eq!(good_sudoku.is_valid(), false);
}

#[test]
fn test4() {
	let good_sudoku = Sudoku{
        data: vec![
                vec![1, 4,  2, 3],
                vec![3, 4, 1, 0],

                vec![4, 1,  3, 2],
                vec![2, 3,  1, 4],
            ]
    };
	assert_eq!(good_sudoku.is_valid(), false);
}

#[test]
fn test5() {
	let good_sudoku = Sudoku{
        data: vec![
                vec![1123, 4,  2, 3],
                vec![3, 2,  4, 1],

                vec![4, 1,  3, 2],
                vec![2, 3,  1, 4],
            ]
    };
	assert_eq!(good_sudoku.is_valid(), false);
}

#[test]
fn test6() {
	let good_sudoku = Sudoku{
        data: vec![
                vec![1, 7,  2, 3],
                vec![3, 2,  4, 1],

                vec![],
                vec![2, 3,  7, 4],
            ]
    };
	assert_eq!(good_sudoku.is_valid(), false);
}

#[test]
fn test7() {
	let good_sudoku = Sudoku{
        data: vec![
                vec![1]
            ]
    };
	assert_eq!(good_sudoku.is_valid(), true);
}

#[test]
fn test8() {
	let bad_sudoku_2 = Sudoku{
        data: vec![
                vec![1,2,3,4,5],
                vec![1,2,3,4],
                vec![1,2,3,4],
                vec![1],
            ]
    };
	assert_eq!(bad_sudoku_2.is_valid(), false);
}

#[test]
fn test9() {
	let bad_sudoku_1 = Sudoku{
        data: vec![
                vec![1,2,3, 4,5,6, 7,8,9],
                vec![1,2,3, 4,5,6, 7,8,9],
                vec![1,2,3, 4,5,6, 7,8,9],

                vec![1,2,3, 4,5,6, 7,8,9],
                vec![1,2,3, 4,5,6, 7,8,9],
                vec![1,2,3, 4,5,6, 7,8,9],

                vec![1,2,3, 4,5,6, 7,8,9],
                vec![1,2,3, 4,5,6, 7,8,9],
                vec![1,2,3, 4,5,6, 7,8,9],
            ]
    };
	assert_eq!(bad_sudoku_1.is_valid(), false);
}

#[test]
fn test10() {
	let bad = Sudoku{
        data: vec![
                vec![1, 1,  2, 3],
                vec![1, 1,  4, 1],

                vec![4, 1,  1, 1],
                vec![2, 3,  1, 1],
            ]
    };
	assert_eq!(bad.is_valid(), false);
}
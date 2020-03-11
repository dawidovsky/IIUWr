mod Population;
mod Dot;
mod Brain;
mod utils;

extern crate wasm_bindgen;

use wasm_bindgen::prelude::*;
use std::fmt;

#[wasm_bindgen]
#[repr(u8)]
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum Cell {
    Empty = 0,
    Dot = 1,
    Brick = 2,
    Goal = 3,
}

#[wasm_bindgen]
pub struct Universe {
    width: u32,
    height: u32,
    cells: Vec<Cell>,
    population: Population::Population,
}

impl Universe {
    fn get_index(&self, row: u32, column: u32) -> usize {
        (row * self.width + column) as usize
    }
}

#[wasm_bindgen]
impl Universe {
    pub fn tick(&mut self) {

        if self.population.allDotsDead() {
            self.population.calculateFitness();
            self.population.naturalSelection();
            self.population.mutateBabies();
        }
        else{
            self.population.update();
        }

        let mut next = self.cells.clone();

        for row in 0..self.height {
            for col in 0..self.width {
                let idx = self.get_index(row, col);
                next[idx] = Cell::Empty;
            }
        }

        next[self.get_index(self.population.getGoalY(), self.population.getGoalX())] = Cell::Goal;

        for dot in self.population.getDots() {
            next[self.get_index(dot.getPositionY(), dot.getPositionX())] = Cell::Dot;
        }

        for i in 0..self.cells.len() {
            if self.cells[i] == Cell::Brick{
                next[i] = Cell::Brick;
            }
        }

        self.cells = next;
    }

    pub fn new() -> Universe {
        let width = 128;
        let height = 128;
        let popCount = 50;
        let goalX = 64;
        let goalY = 5;
        let population = Population::Population::new(popCount, goalX, goalY);

        let mut cells: Vec<Cell> = vec![];
        for i in 0..width*height {
            cells.push(Cell::Empty);
        }
        cells[(goalX * goalX) as usize] = Cell::Goal;
        for dot in population.getDots().iter() {
            cells[(dot.getPositionX() * dot.getPositionY()) as usize] = Cell::Dot;
        }

        Universe {
            width,
            height,
            cells,
            population,
        }
    }

    pub fn cells(&self) -> *const Cell {
        self.cells.as_ptr()
    }

}

impl fmt::Display for Universe {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        for line in self.cells.as_slice().chunks(self.width as usize) {
            for &cell in line {
                let mut symbol: char;
                if cell == Cell::Empty { symbol = '◻' }
                if cell == Cell::Dot { symbol = '◼' }
                if cell == Cell::Goal { symbol = '©' }
                else { symbol = '§' }
                write!(f, "{}", symbol)?;
            }
            write!(f, "\n")?;
        }

        Ok(())
    }
}

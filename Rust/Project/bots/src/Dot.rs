use crate::Brain;

extern crate console_error_panic_hook;
use std::panic;

pub struct Dot{
    positionX: u32,
    positionY: u32,
    brain: Brain::Brain,
    isDead: bool,
    reachedGoal: bool,
    isBest: bool,
    fitness: f32,
}

impl Dot {

    pub fn new() -> Dot {
        panic::set_hook(Box::new(console_error_panic_hook::hook));
        let positionX = 64;
        let positionY = 42;
        let brain = Brain::Brain::new(1000);
        let isDead = false;
        let reachedGoal = false;
        let isBest = false;
        let fitness = 0.0;

        Dot {
            positionX,
            positionY,
            brain,
            isDead,
            reachedGoal,
            isBest,
            fitness,
        }
    }

    pub fn baby(&self) -> Dot {
        let mut baby: Dot = Dot::new();
        baby.brain = self.brain.clone();
        baby
    }

    pub fn getPositionX(&self) -> u32 {
        self.positionX
    }

    pub fn getPositionY(&self) -> u32 {
        self.positionY
    }

    pub fn getFitness(&self) -> f32 {
        self.fitness
    }

    pub fn getBrain(&self) -> Brain::Brain {
        self.brain.clone()
    }

    pub fn setBest(&mut self) -> () {
        self.isBest = true;
    }

    pub fn reachedGoal(&self) -> bool {
        self.reachedGoal
    }

    pub fn isItDead(&self) -> bool {
        self.isDead
    }

    pub fn clone(&self) -> Dot {
        let mut new_dot = Dot::new();
        new_dot.positionX = self.positionX;
        new_dot.positionY = self.positionY;
        new_dot.brain = self.brain.clone();
        new_dot.isDead = self.isDead;
        new_dot.reachedGoal = self.reachedGoal;
        new_dot.isBest = self.isBest;
        new_dot.fitness = self.fitness;
        new_dot
    }

    pub fn calculateFitness(&mut self, goalX: u32, goalY: u32) -> () {
        if self.reachedGoal {
            self.fitness = 1.0/16.0 + 10000.0/((self.brain.getSteps() * self.brain.getSteps()) as f32);
        } else {
            let distanceToGoal: f32 = Dot::dist(self.positionX, self.positionY, goalX, goalY);
            self.fitness = 1.0/(distanceToGoal * distanceToGoal);
        }
    }

    fn dist(x1: u32, y1: u32, x2: u32, y2: u32) -> f32 {
        (((x2 as i32 - x1 as i32) as f32).powf(2.0) + ((y2 as i32 - y1 as i32) as f32).powf(2.0)).sqrt()
    }

    pub fn dotMove(&mut self) -> () {
        if self.brain.getSteps() < self.brain.getDirections().len() {
            let direction = self.brain.getDirections()[self.brain.getSteps()];
            if direction%3 == 0 { self.positionX -= 1 }
            if direction%3 == 2 { self.positionX += 1 }
            if direction < 3    { self.positionY -= 1 }
            if direction > 5    { self.positionY += 1 }
        } else { self.isDead = true; }
    }

    pub fn update(&mut self, goalX: u32, goalY: u32) -> () {
        let width = 128;
        let height = 128;
        if !self.isDead && !self.reachedGoal {
            self.dotMove();
            if self.positionX < 2 || self.positionY < 2 || self.positionX > width-2 || self.positionY > height -2 {
                self.isDead = true;
            }
            else if Dot::dist(self.positionX, self.positionY, goalX, goalY) < 1.0 {
                self.isDead = true;
            }
        }
    }

    pub fn showPosition(&self) -> () {
        println!("posX: {}, posY: {}, isWon: {}", self.positionX, self.positionY, self.isDead);
    }
}
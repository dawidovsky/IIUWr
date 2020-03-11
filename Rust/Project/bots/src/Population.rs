use crate::Dot;

extern crate console_error_panic_hook;
use std::panic;

use rand::prelude::*;

pub struct Population{
    dots: Vec<Dot::Dot>,
    fitnessSum: f32,
    gen: i32,
    bestDot: usize,
    minStep: i32,
    goalX: u32,
    goalY: u32,
}

impl Population{
    pub fn new(size: usize, goalX: u32, goalY: u32) -> Population {
        panic::set_hook(Box::new(console_error_panic_hook::hook));
        let mut dots = Vec::<Dot::Dot>::new();
        let fitnessSum = 0.0;
        let gen = 1;
        let bestDot = 0;
        let minStep = 1000;


        for _ in 0..size {
            dots.push(Dot::Dot::new());
        }

        Population {
            dots,
            fitnessSum,
            gen,
            bestDot,
            minStep,
            goalX,
            goalY,
        }
    }

    pub fn getDots(&self) -> Vec<Dot::Dot> {
        let mut new_vec: Vec<Dot::Dot> = Vec::new();
        for dot in self.dots.iter() {
            new_vec.push(dot.clone());
        }
        new_vec
    }

    pub fn getGoalX(&self) -> u32 {
        self.goalX
    }

    pub fn getGoalY(&self) -> u32 {
        self.goalY
    }

    pub fn update(&mut self) -> () {
        for i in 0..self.dots.len() {
            self.dots[i].update(self.goalX, self.goalY);
        }
    }

    pub fn show(&self) -> () {
        for dot in self.dots.iter() {
            dot.showPosition();
        }
    }

    pub fn calculateFitness(&mut self) -> () {
        for i in 0..self.dots.len() {
            self.dots[i].calculateFitness(self.goalX, self.goalY);
        }
    }

    pub fn allDotsDead(&self) -> bool {
        for dot in self.dots.iter() {
            if !dot.isItDead() && !dot.reachedGoal() {
                return false
            }
        }
        return true
    }

    pub fn naturalSelection(&mut self) -> () {
        let mut newDots: Vec<Dot::Dot> = Vec::new();
        self.setBestDot();
        self.calculateFitnessSum();

        newDots.push(self.dots[self.bestDot].baby());
        newDots[0].setBest();
        for _ in self.dots.iter() {
          let parent: Dot::Dot = self.selectParent();
          newDots.push(parent.baby());
        }

        self.dots = newDots;
        self.gen += 1;
    }

    pub fn calculateFitnessSum(&mut self) -> () {
        let mut sum = 0.0;
        for dot in self.dots.iter() {
            sum += dot.getFitness();
        }
        self.fitnessSum = sum;
    }

    pub fn selectParent(&self) -> Dot::Dot {
        let mut rng = thread_rng();
        let rand: f32 = rng.gen_range(0.0, self.fitnessSum);

        let mut runningSum = 0.0;

        for i in 0..self.dots.len() {
            runningSum += self.dots[i].getFitness();
            if runningSum > rand {
                return self.dots[i].clone();
            }
        }
        return Dot::Dot::new();
    }

    pub fn mutateBabies(&self) -> () {
        for dot in self.dots.iter() {
            dot.getBrain().mutate();
        }
    }

    pub fn setBestDot(&mut self) -> () {
        let mut max = 0.0;
        let mut maxIndex = 0;
        for i in 0..self.dots.len() {
            if self.dots[i].getFitness() > max {
                max = self.dots[i].getFitness();
                maxIndex = i;
            }
        }

        self.bestDot = maxIndex;

        if self.dots[self.bestDot].reachedGoal() {
            self.minStep = self.dots[self.bestDot].getBrain().getSteps() as i32;
        }
    }
}
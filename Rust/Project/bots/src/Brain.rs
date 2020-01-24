use rand::prelude::*;

pub struct Brain{
    directions: Vec<u8>,
    step: usize,
}

impl Brain {

    pub fn getSteps(&self) -> usize {
        self.step
    }

    pub fn getDirections(&self) -> Vec<u8> {
        self.directions.clone()
    }

    pub fn new(size: usize) -> Brain {
        let mut directions: Vec<u8> = vec![];
        let step = 0;
        let mut rng = thread_rng();

        for _ in 0..size {
            let random = rng.gen_range(0, 9);
            directions.push(random);
        }

        Brain {
            directions,
            step,
        }
    }

    pub fn clone(&self) -> Brain {
        let mut clone: Brain = Brain::new(self.directions.len());
        clone.directions = self.directions.clone();
        clone
    }

    pub fn mutate(&mut self) -> () {
        let mutationRate: f32 = 0.01;
        let mut rng = rand::thread_rng();

        for i in 0..self.directions.len() {
            let random = rng.gen_range(0.0, 1.0);
            if random < mutationRate {
                let randomDir = rng.gen_range(0, 9);
                self.directions[i] = randomDir;
            }
        }
    }
}
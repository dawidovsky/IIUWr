
extern crate stdweb;
extern crate console_error_panic_hook;
use self::stdweb::js;
use std::panic;

pub struct Brain{
    directions: Vec<u8>,
    step: usize,
}
// js!(js random) WebAssembly random
impl Brain {

    pub fn getSteps(&self) -> usize {
        self.step
    }

    pub fn getDirections(&self) -> Vec<u8> {
        self.directions.clone()
    }

    pub fn new(size: usize) -> Brain {
        panic::set_hook(Box::new(console_error_panic_hook::hook));
        let mut directions: Vec<u8> = vec![];
        let step = 0;
        let mut rng = js!{
            Math.floor(Math::random(10));
        };

        for _ in 0..size {
            let random = js!{
                Math.floor(Math::random(10));
            };
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

        for i in 0..self.directions.len() {
            let random = js!{
                Math.floor(Math::random(10));
            };
            if random < mutationRate {
                let randomDir = rng.gen_range(0, 9);
                self.directions[i] = randomDir;
            }
        }
    }
}
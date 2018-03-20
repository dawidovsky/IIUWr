#lang racket

(define (dist x y)
  (abs (- x y)))

(define (square x)
  (* x x))

(define (cube x)
  (* x x x))

(define (cube-root x)
  (define (improve y)
  (/ (+ (/ x (square y)) (* 2 y)) 3))
  (define (good-enough? approx)
    (< (dist x (cube approx)) 0.0001))
  (define (iter approx)
    (cond
      [(good-enough? approx) approx]
      [else                  (iter (improve approx))]))
  
  (iter 1.0))

(cube-root 27) ;; 3
(cube-root 1) ;; 1
(cube-root 5) ;; 1.70
(cube-root 123) ;; 4.97
(cube-root 1000) ;; 10

#lang racket

(define (square x) (* x x))

(define (inc x) (+ x 1))

(define (inc2 x) (+ x 2))

(define (compose f g) (lambda (x) (f (g x))))

(define (identity x) x)

(define (repeated p n)
  (lambda (x)
    (if(= n 0)
    (identity x)
    ((compose (repeated p (- n 1)) p) x))))

(define sum
  (lambda (term next s e)
    (if (> s e)
        0
        (+ (term s) (sum term next (next s) e)))))

(define (product term next s e)
    (if (> s e)
        1.0
        (* (term s) (product term next (next s) e))))

(define (product-iter prod term next s e)
    (if (> s e)
        prod
        (product-iter (* prod (term s)) term next (next s) e)))


(define (cont-frac num den k)
  (if(= k 0)
  1.0
  (/ (num k) (+ (den k) (cont-frac num den (- k 1))))))


(define (cont-frac-iter num den k)
  (define (cont k iter)
    (if (= k 0)
        iter
        (cont (- k 1) (/ (num k) (+ (den k) iter)))))
(cont k 1.0))

;(cont-frac (lambda (i) 1.0) (lambda (i) 1.0) 1000)

(define (pi-cont k)
  (+ (cont-frac-iter (lambda (x) (square (- (* x 2) 1))) (lambda (x) 6.0) k) 3.0))

;(define (PI)
;  (define (iter k)
;    (let ((pi-co (pi-cont k)))
;      (if (

(define (atan-cf x k)
  (cont-frac-iter (lambda (i)
               (if (= i 1)
                   x
                   (square (* (- i 1) x))))
             (lambda (i)
               (- (* 2 i) 1)) k))

(define (build n d b)
  (/ n (+ d b)))

(define (repeated-build k n d b)
  (repeated (lambda (b) (build n d b)) k)b)
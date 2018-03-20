#lang racket

(define (square x) (* x x))

(define (dist x y)
  (abs (- x y)))

(define (close-enough? x y)
   (< (dist x y) 0.0000001))

(define (func N D x)
  
  ;; liczenie licznika 
  (define (num N D n)
    (cond [(= -1 n) 1]
           [(= 0 n) 0]
           [else
            (+ (* (D n) (num N D (- n 1))) (* (N n x) (num N D (- n 2))))]))
  
  ;; liczenie dzielnika 
  (define (den N D n)
    (cond [(= -1 n) 0]
          [(= 0 n) 1]
          [else
           (+ (* (D n) (den N D (- n 1))) (* (N n x) (den N D (- n 2))))]))
  
 ;; funkcja pomocnicza licząca ułamek o głębokości n
  (define (helper n)
    (/ (num N D n) (den N D n)))

 ;; liczę ułamek o n-tej głębokości i porównuje go z ułamkiem o głębokości
 ;; n+1. Jeśli są wystarczająco podobne to zwracam wartość ułamka o n-tej
 ;; głębokości. Jeśli nie, zapamiętuje ułamek o n-tej głębokości i
 ;; przechodzę do n+1.
  (define (func-iter old-product N D n)
    (let ((product (helper n)))
      (if (close-enough? old-product product)
          old-product
          (func-iter product N D (+ n 1)))))
  
  ;; ułamek o n=0 jest równy 0 i od tego zaczynam zapamiętywanie, a pierwszym
  ;; ułamkiem jaki liczę jest ułamek o głębokości 1
  (func-iter 0.0 N D 1))

;; wywołania atan z zadania 8 i funkcji wbudowanej atan
(func (lambda (i x) (if (= i 1) x (square (* (- i 1) x))))
      (lambda (i) (- (* 2 i) 1))
       0.0)
 
(atan 0.0)

(func (lambda (i x) (if (= i 1) x (square (* (- i 1) x))))
      (lambda (i) (- (* 2 i) 1))
       2.0)
 
(atan 2.0)

(func (lambda (i x) (if (= i 1) x (square (* (- i 1) x))))
      (lambda (i) (- (* 2 i) 1))
       1.0)
 
(atan 1.0)


(func (lambda (i x) (if (= i 1) x (square (* (- i 1) x))))
      (lambda (i) (- (* 2 i) 1))
       -2.0)
 
(atan -2.0)

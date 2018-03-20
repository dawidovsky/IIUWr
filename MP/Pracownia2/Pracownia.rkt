#lang racket

(define (dist x y)
  (abs (- x y)))

;; funkcje z zajęć
(define (compose f g) (lambda (x) (f (g x))))

(define (identity x) x)

(define (repeated p n)
  (lambda (x)
    (if(= n 0)
    (identity x)
    ((compose (repeated p (- n 1)) p) x))))


;; funkcje z wykładu
(define (close-enough? x y)
  (< (dist x y) 0.00001))

(define (fixed-point f x0)
  (let ((x1 (f x0)))
    (if (close-enough? x0 x1)
        x0
        (fixed-point f x1))))

(define (average-damp f)
  (lambda (x) (/ (+ x (f x)) 2)))

;; funcka licząca logarytm o podstawie 2
;; wprowadzając ręcznie kolejne liczby naturalne do funkcji nth-root
;; w miejscu (floor (log2 n) zauważyłem że program się zapętla dla kolejnych
;; potęg dwójki, więc liczba tłumień jaka jest stosowana dla kolejnych
;; pierwiastków jest równa zaokrąglonej w dół liczbie log o podstawie 2 z n
(define (log2 x)
  (/ (log x) (log 2)))

(define (nth-root x n)
  (fixed-point
      ((repeated average-damp (floor (log2 n)))
          (lambda (y) (/ x (expt y (- n 1))))) 1.0))
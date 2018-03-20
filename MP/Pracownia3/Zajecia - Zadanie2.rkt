#lang racket

(define (dist x y)
  (abs (- x y)))

(define (average x y)
  (/ (+ x y) 2))

(define (square x)
  (* x x))

(define (sqrt x)
  (define (improve approx)
    (average (/ x approx) approx))
  (define (good-enough? approx)
    (< (dist x (square approx)) 0.00001))
  (define (iter approx)
    (cond
      [(good-enough? approx) approx]
      [else                  (iter (improve approx))]))
  
  (iter 1.0))

(define (point-x x) (car x))
(define (point-y x) (cdr x))
(define (make-point x y) (cons x y))
(define (point? x)
  (if (pair? x)
      #t
      #f))

(define point1 (make-point 1 5))
(define point2 (make-point 5 5))
(define point3 (make-point 1 3))
(define point4 (make-point 2 5))

(define (display-point p)
  (display "(")
  (display (point-x p))
  (display ", ")
  (display (point-y p))
  (display ")"))

(define (vect-begin vec) (car vec))
(define (vect-end vec) (cdr vec))
(define (make-vect x y) (cons x y))
(define (vect? x)
  (if (and (pair? x) (pair? (car x)) (pair? (cdr x)))
      #t
      #f))

(define vec1 (make-vect point1 point2))
(define vec2 (make-vect point3 point4))

(define (display-vect v)
  (display "[")
  (display-point (vect-begin v))
  (display ", ")
  (display-point (vect-end v))
  (display "]"))

(define (vect-length vec)
  (sqrt (+ (square (- (car (cdr vec)) (car (car vec))))
           (square(- (cdr (cdr vec)) (cdr (car vec)))))))

(define (vect-scale v k)
  (let ([x (+ (car (vect-begin v))
             (* k (- (car (vect-end v)) (car (vect-begin v)))))]
       [y (+ (cdr (vect-begin v))
             (* k (- (cdr (vect-end v)) (cdr (vect-begin v)))))])
    (make-vect (vect-begin v) (make-point x y))))
    
(define (vect-translate vec p)
  (make-vect p (make-point (+ (car p) (- (car (cdr vec)) (car (car vec))))
                           (+ (cdr p) (- (cdr (cdr vec)) (cdr (car vec)))))))

(define (make-v p alfa l)
  (if (and (point? p) (>= alfa 0) (< alfa (* 2 pi)) (>= l 0))
      (cons p (cons alfa l))
      #f))

(define (vec-b v)
  (if (vect? v)
      (car v)
      #f))

(define (vec-alfa v)
  (cadr v))

(define (vec-len v)
  (car (cdr (cdr v))))

(define (scale-vec v k)
  (if (vect? v)
      (make-v (vec-b v)
              (vec-alfa v)
              (* k (vec-len v)))
      #f))

(define (trans-vec v p)
  (if( (and (vect? v) (point? p)))
       (make-v p (vec-alfa v) (vec-len v))
       #f))

(define (reverse-iter L)
 (define (iter L acc)
  (if (null? L)
     acc
    (iter (cdr L) (cons (car L) acc))))
(iter L null))

(define (reverse-rec L)
  (if (null? L)
      L
      (append (reverse-rec (cdr L)
                           (list car L)))))

(define L (list 3 1 4))

(define (insert L n)
  (if (or (null? L) (> (cdr L) n))
      (cons n L)
      (cons (car L) (insert (cdr L) n))))
 
(define (sort L)
  (define (helper L2 L)
    (if (null? L)
        L2
        (helper (insert L2 (car L)) (cdr L))))
    (helper null L))

(define (better-sort L)
    (if (null? L)
        null
        (insert  (better-sort (cdr L)) car L)))
  
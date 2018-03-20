#lang racket

(define (make-rat n d)
  (if (= d 0)
      (display "blad - nie dzielimy przez zero")
  (list n d)))

(define (rat-num x)
  (let ((g (gcd (car x) (car (cdr x)))))
    (/ (car x) g)))

(define (rat-den x)
  (let ((g (gcd (car x) (car (cdr x)))))
    (/ (car (cdr x)) g)))

(define (rat? ul)
  (if (and (list? ul) (list? (cdr ul)) (null? (cdr (cdr ul))))
      #t
      #f))

(define (display-rat ul)
  (display (rat-num ul))
  (display "/")
  (display (rat-den ul)))

(define ul1 (make-rat 1 3))
(define ul2 (make-rat 1 2))
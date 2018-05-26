#lang racket

;; --------------------------------Sufiksy-------------------------------------

(define/contract (suffixes xs)
  (let ([a (new-∀/c 'a)])
    (-> (listof a) (listof (listof a))))
  (if (null? xs)
      (list null)
      (cons xs (suffixes (cdr xs)))))

;; ------------------------------Sqrt-------------------------------------------

(define/contract (dist x y)
  (-> number? number? number?)
  (abs (- x y)))

(define/contract (average x y)
  (-> number? number? number?)
  (/ (+ x y) 2))

(define/contract (square x)
  (-> number? number?)
  (* x x))

(define/contract (sqrt x)
  (->i ([x positive?])
       [result positive?]
       #:post (x result)
       (if (< (dist x (square result)) 0.0001)
           #t
           #f))
  (define (improve approx)
    (average (/ x approx) approx))
  (define (good-enough? approx)
    (< (dist x (square approx)) 0.0001))
  (define (iter approx)
    (cond
      [(good-enough? approx) approx]
      [else                  (iter (improve approx))]))
  (iter 1.0))

;; ----------------------------Filter-----------------------------------------

(define/contract (filter p? xs)
  (let ([a (new-∀/c 'a)])
    (-> (-> a boolean?) (listof a) (listof a)))
  (if (null? xs)
      null
      (if (p? (car xs))
          (cons (car xs) (filter p? (cdr xs)))
          (filter p? (cdr xs)))))

(define/contract (filter-zal p? xs)
  (and/c
   (let ([a (new-∀/c 'a)])
     (-> (-> a boolean?) (listof a) (listof a)))
   (->i ([p? (-> any/c boolean?)]
         [xs (listof any/c)])
        [result (listof any/c)]
        #:post (p? result)
        (andmap p? result)))
  (if (null? xs)
      null
      (if (p? (car xs))
          (cons (car xs) (filter-zal p? (cdr xs)))
          (filter-zal p? (cdr xs)))))

;; --------------------------Monoid-----------------------------------

(define-signature monoid^
  ((contracted
    [elem? (-> any/c boolean?)]
    [neutral elem?]
    [oper (-> elem? elem? elem?)])))

(define-unit monoid-int@
  (import)
  (export monoid^)
  (define elem? integer?)
  (define neutral 0)
  (define oper +))

(define-unit monoid-list@
  (import)
  (export monoid^)
  (define elem? list?)
  (define neutral null)
  (define oper append))

;(define-values/invoke-unit/infer monoid-int@)
(define-values/invoke-unit/infer monoid-list@)

;; ----------------------------Quickckeck----------------------------------------

(require quickcheck)

;(quickcheck
; (property
;  ([l arbitrary-integer]
;   [k arbitrary-integer]
;   [m arbitrary-integer])
;  (= (oper l neutral) (oper neutral l))
;  (= (oper (oper l k) m) (oper l (oper k m)))
;  (= l (oper neutral l))))

(define arbitrary-mylist (arbitrary-list arbitrary-integer))

(quickcheck
 (property
  ([l arbitrary-mylist]
   [k arbitrary-mylist]
   [m arbitrary-mylist])
  (equal? (oper l neutral) (oper neutral l))
  (equal? (oper (oper l k) m) (oper l (oper k m)))
  (equal? l (oper neutral l))))

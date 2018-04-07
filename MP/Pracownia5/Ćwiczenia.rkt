#lang racket

(define (var? t)
  (symbol? t))

(define (neg? t)
  (and
   (list? t)
   (= 2 (length t))
   (eq? 'neg (car t))))

(define (conj? t)
  (and
   (list? t)
   (= 3 (length t))
   (eq? 'conj (car t))))

(define (disj? t)
  (and
   (list? t)
   (= 3 (length t))
   (eq?'disj (car t))))

(define (prop? f)
(or (var? f)
    (and (neg? f)
         (prop? (neg-subf f)))
    (and(disj? f)
        (prop? (disj-left f))
        (prop? (disj-rght f)))
    (and(conj? f)
        (prop? (conj-left f))
        (prop? (conj-rght f)))))

(define (neg x)
  (list 'neg x))

(define (conj x y)
  (list 'conj x y))

(define (disj x y)
  (list 'disj x y))

(define (neg-subf f)
  (cadr f))

(define (disj-left f)
  (cadr f))

(define (disj-rght f)
  (caddr f))

(define (conj-left f)
  (cadr f))

(define (conj-rght f)
  (caddr f))

(define formula (conj (conj 'p 'q) (disj 'p 'q)))
(define con (conj 'a 'b))

(define (free-vars form)
  (define (helper res lis)
    (cond [(neg? res) (helper (neg-subf res) lis)]
          [(disj? res) (helper (disj-rght res)
                                (helper (disj-left res) lis))]
          [(conj? res) (helper (conj-rght res)
                                (helper (conj-left res) lis))]
          [else (remove-duplicates (append lis (list res)))]))
  (helper form '()))

(free-vars formula)
(free-vars con)

;; z zajęć
;; generator wszystkich wartościowań z listy zmiennych
(define (gen-vals xs)
  (if (null? xs)
      (list  null)
      (let*
          ((vss   (gen-vals (cdr xs)))
           (x     (car xs))
           (vst   (map(lambda(vs) (cons (list x true)   vs)) vss))
           (vsf   (map(lambda(vs) (cons (list x false) vs)) vss)))
        (append  vst  vsf))))

;; tworzy listę zmiennych wolnych
(define (free-vars form)
  (define (helper wynik res)
    (cond [(null? res) wynik]
          [(sorted-varlist? res) (merge-vars res wynik)]
          [(res-clause? (car res))
           (merge-vars wynik
                       (merge-vars (helper wynik (second (car res)))
                                   (helper wynik (third (car res))))
                       )]
          [else (helper wynik (cdr res))]))
  (helper '() form))

;; sprawdzamy czy dla danego wartościowania klauzula jest spełnialna
(define (satisfiable? list-bool res)
  (let ((pos (cadr res))
        (neg (caddr res)))
    (define (sat-pos bool)
      

#lang racket

(define (inc n)
  (+ n 1))

;;; ordered elements
(define (make-elem pri val)
  (cons pri val))

(define (elem-priority x)
  (car x))

(define (elem-val x)
  (cdr x))

;;; leftist heaps (after Okasaki)

;; data representation
(define leaf 'leaf)

(define (leaf? h) (eq? 'leaf h))

(define (hnode? h)
  (and (list? h)
       (= 5 (length h))
       (eq? (car h) 'hnode)
       (natural? (caddr h))))

;;napisane przy współpracy z
;;Bartosz Sobocki

;;Wierzchołek tworzymy zgodnie z opisem zadania a rangę ustalamy wybierając
;;wyższą rangę z dwóch danych kopców i dodając do niej jeden.
(define (make-node elem heap-a heap-b)
  (if (>= (rank heap-a) (rank heap-b))
      (list 'hnode elem (+ (rank heap-b) 1) heap-a heap-b)
      (list 'hnode elem (+ (rank heap-a) 1) heap-b heap-a)))

(define (node-elem h)
  (second h))

(define (node-left h)
  (fourth h))

(define (node-right h)
  (fifth h))

(define (hord? p h)
  (or (leaf? h)
      (<= p (elem-priority (node-elem h)))))

(define (heap? h)
  (or (leaf? h)
      (and (hnode? h)
           (heap? (node-left h))
           (heap? (node-right h))
           (<= (rank (node-right h))
               (rank (node-left h)))
           (= (rank h) (inc (rank (node-right h))))
           (hord? (elem-priority (node-elem h))
                  (node-left h))
           (hord? (elem-priority (node-elem h))
                  (node-right h)))))

(define (rank h)
  (if (leaf? h)
      0
      (third h)))

;; operations

(define empty-heap leaf)

(define (heap-empty? h)
  (leaf? h))

(define (heap-insert elt heap)
  (heap-merge heap (make-node elt leaf leaf)))

(define (heap-min heap)
  (node-elem heap))

(define (heap-pop heap)
  (heap-merge (node-left heap) (node-right heap)))


;;napisane przy współpracy z
;;Bartosz Sobocki
;;Wojtek Bogucki

;;Najpierw wybieramy mniejszy priorytet z heap-min z obu kopców
;;Następnie tworzymy wierzchołek o elemencie z kopca wybranego wcześniej
;;Jego podrzewa wybieramy w następujący sposób:
;;- lewym podrzewem jest lewe podrzewo kopca o elemencie o mniejszym priorytecie
;;- prawym podrzewem jest rekurencyjnie tworzony kopiec łączony z prawego
;;podrzewa kopca wybranego wcześniej i drugiego kopca.
(define (heap-merge h1 h2)
  (cond
   [(leaf? h1) h2]
   [(leaf? h2) h1]
   [(> (elem-priority (heap-min h1)) (elem-priority (heap-min h2)))
        (make-node (heap-min h2) (node-left h2) (heap-merge (node-right h2) h1))]
   [else (make-node (heap-min h1) (node-left h1) (heap-merge (node-right h1) h2))]))


;;; heapsort. sorts a list of numbers.
(define (heapsort xs)
  (define (popAll h)
    (if (heap-empty? h)
        null
        (cons (elem-val (heap-min h)) (popAll (heap-pop h)))))
  (let ((h (foldl (lambda (x h)
                    (heap-insert (make-elem x x) h))
            empty-heap xs)))
    (popAll h)))

;;; check that a list is sorted (useful for longish lists)
(define (sorted? xs)
  (cond [(null? xs)              true]
        [(null? (cdr xs))        true]
        [(<= (car xs) (cadr xs)) (sorted? (cdr xs))]
        [else                    false]))

;;; generate a list of random numbers of a given length
(define (randlist len max)
  (define (aux len lst)
    (if (= len 0)
        lst
        (aux (- len 1) (cons (random max) lst))))
  (aux len null))

;;testy
;;tworzymy listy o losowych elementach i poddajemy je sortowaniu
;;oraz sprawdzamy czy przechodzą predykat "sorted?".
(define first_test (randlist 10 1000))
 first_test
(heapsort first_test)
(sorted? (heapsort first_test))
(define second_test (randlist 20 3))
 second_test
(heapsort second_test)
(sorted? (heapsort second_test))
(define third_test (randlist 5 1000000))
 third_test
(heapsort third_test)
(sorted? (heapsort third_test))
(define fourth_test (randlist 13 50))
 fourth_test
(heapsort fourth_test)
(sorted? (heapsort fourth_test))

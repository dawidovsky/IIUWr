#lang typed/racket

;;; drzewa binarne

(define-type Leaf 'leaf)
(define-type (Node A B) (List 'node A B B))
(define-type (Tree A) (U Leaf (Node A (Tree A))))

(define-predicate leaf? Leaf)
(define-predicate node? (Node Any Any))
(define-predicate tree? (Tree Any))

(: leaf Leaf)
(define leaf 'leaf)

(: node-val (All (A B) (-> (Node A B) A)))
(define (node-val x)
  (cadr x))

(: node-left (All (A B) (-> (Node A B) B)))
(define (node-left x)
  (caddr x))

(: node-right (All (A B) (-> (Node A B) B)))
(define (node-right x)
  (cadddr x))

(: make-node (All (A B) (-> A B B (Node A B))))
(define (make-node v l r)
  (list 'node v l r))

;;; wyszukiwanie i wstawianie w drzewach przeszukiwañ binarnych

(: bst-find (-> Integer (Tree Integer) Boolean))
(define (bst-find x t)
  (cond [(leaf? t)          false]
        [(= x (node-val t)) true]
        [(< x (node-val t)) (bst-find x (node-left t))]
        [else (bst-find x (node-right t))]))

(: bst-insert (-> Integer (Tree Integer) (Tree Integer)))
(define (bst-insert x t)
  (cond [(leaf? t)
         (make-node x leaf leaf)]
        [(< x (node-val t))
         (make-node (node-val t)
                    (bst-insert x (node-left t))
                    (node-right t))]
        [else
         (make-node (node-val t)
                    (node-left t)
                    (bst-insert x (node-right t)))]))


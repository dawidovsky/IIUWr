#lang racket

(define (concatMap f xs)
  (if (null? xs)
      null
      (append (f (car xs)) (concatMap f (cdr xs)))))

(define (from-to s e)
  (if (= s e)
      (list s)
      (cons s (from-to (+ s 1) e))))


(define (queens board-size)
  ;; Return the representation of a board with 0 queens inserted
  (define (empty-board)
    null)
  ;; Return the representation of a board with a new queen at
  ;; (row, col) added to the partial representation `rest'
  (define (adjoin-position row col rest)
    (cons row rest)
    )
  ;; Return true if the queen in k-th column does not attack any of
  ;; the others
  (define (safe? k positions)
    (let ([first (car positions)])
      (define (iter up down rest)
        (if (null? rest)
            #t
            (let ([check (car rest)])
              (cond ([= first check] #f)
                    ([= check up] #f)
                    ([= check down] #f)
                    (else  (iter (- up 1) (+ down 1) (cdr rest)))))))
      (iter (- first 1) (+ first 1) (cdr positions))))
          
    
  ;; Return a list of all possible solutions for k first columns
  (define (queen-cols k)
    (if (= k 0)
        (list (empty-board))
        (filter
         (lambda (positions) (safe? k positions))
         (concatMap
          (lambda (rest-of-queens)
            (map (lambda (new-row)
                   (adjoin-position new-row k rest-of-queens))
                 (from-to 1 board-size)))
          (queen-cols (- k 1))))))
  (queen-cols board-size))

;; Mirror
;; (define (mirror t)
;; (cond ([(not (btree? t) false]
;;       [(eq? 'leaf t) 'leaf]
;;       [else (list 'node (cadr t) (mirror (cadddr t)) (mirror (caddr t))



;; Flatten
;; (define (flatten t acc)
;;   (if (eq? t 'leaf)
;;    acc
;;    (flatten (caddr t) (cons (cadr t) (flatten (cadddr t) acc)))

;; Sort
;; (define (treesort l)
;;   (define (helper l tree)
;;     (if (null? l)
;;          tree
;;          (helper (cdr l) (bst-insert (car l) tree))))
;;    (flatten (helper l 'leaf)))

;;Delete
;; (define (delete tree x)
;;    (cond [(null? tree) null]
;;          [= x (node-val tree)
;;               (if (eq? (node-right tree) 'leaf))
;;                   (node-left tree)
;;                   (let ([m (bst-min (bst-right tree))])
;;                            (make-node m (node-left tree) (delete (node-right tree) m))
;;          [(> x (node-val tree)) (make-node (node-val tree) (node-left tree) (delete (node-right tree) x)))]
;;          [else (make-node (node-val tree) (delete (node-left tree) x) (node-right tree))])))

;;BST-MIN
;; (define (bst-min tree)
;;    (if (eq? 'leaf (node-left tree))
;;        (node-val tree)
;;        (bst-min (node-left tree)))
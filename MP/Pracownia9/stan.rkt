#lang racket

;; pomocnicza funkcja dla list tagowanych o określonej długości

(define (tagged-tuple? tag len p)
  (and (list? p)
       (= (length p) len)
       (eq? (car p) tag)))

(define (tagged-list? tag p)
  (and (pair? p)
       (eq? (car p) tag)
       (list? (cdr p))))
;;

(define (node l s r)
  (list 'node l s r))

(define (node? n)
  (tagged-tuple? 'node 4 n))

(define (node-left n)
  (second n))

(define (node-middle n)
  (third n))

(define (node-right n)
  (fourth n))

(define (leaf? n)
  (or (symbol? n)
      (number? n)
      (null? n)))

;;

(define (res v s)
  (cons v s))

(define (res-val r)
  (car r))

(define (res-state r)
  (cdr r))

;;

(define (rename t)
  (define (rename-st t i)
    (cond [(leaf? t) (res i (+ i 1))]
          [(node? t)
           (let* ([rl (rename-st (node-left t) i)]
                  [rr (rename-st (node-right t) (res-state rl))])
             (res (node (res-val rl) (res-val rr))
                  (res-state rr)))]))
  (res-val (rename-st t 0)))

;;

(define (st-app f x y)
  (lambda (i)
    (let* ([rx (x i)]
           [ry (y (res-state rx))])
      (res (f (res-val rx) (res-val ry))
           (res-state ry)))))

(define get-st
  (lambda (i)
    (res i i)))

(define (modify-st f)
  (lambda (i)
    (res null (f i))))

;;

(define (inc n)
  (+ n 1))

(define (rename2 t)
  (define (rename-st t)
    (cond [(leaf? t)
           (multi-st-app (lambda (x y) x)
                   get-st
                   (modify-st inc))] ;; jak chce losowe to zamiast całego multi-st-app daje (rand 1000)
          [(node? t)
           (multi-st-app node
                   (rename-st (node-left  t))
                   (rename-st (node-middle  t))
                   (rename-st (node-right t)))]))
  (res-val ((rename-st t) 0)))

(define (rand  max)
  (lambda (seed)
    (let ([v (modulo  (+ (*  1103515245  seed) 12345) (expt 2 32))])
      (res (modulo v max) v))))

(define (multi-st-app f . args)
  (define (helper xs i)
    (if (null? xs)
        null
        (let ((result ((car xs) i)))
          (cons result (helper (cdr xs) (res-state result))))))
  (lambda (i)
    (let ((result (helper args i)))
      (res (apply f (map res-val result))
           (res-state (last result))))))
             
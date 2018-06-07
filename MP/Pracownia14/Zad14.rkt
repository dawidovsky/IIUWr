#lang racket

;; --------------Konta------------------ ;;

;;; rozdział 3.1.1

(define balance 100)

(define (withdraw amount)
  (if (>= balance amount)
      (begin (set! balance (- balance amount))
             balance)
      "Insufficient funds"))

;: (withdraw 25)
;: (withdraw 25)
;: (withdraw 60)
;: (withdraw 15)

(define new-withdraw
  (let ((balance 100))
    (lambda (amount)
      (if (>= balance amount)
          (begin (set! balance (- balance amount))
                 balance)
          "Insufficient funds"))))


(define (make-withdraw balance)
  (lambda (amount)
    (if (>= balance amount)
        (begin (set! balance (- balance amount))
               balance)
        "Insufficient funds")))


;: (define W1 (make-withdraw 100))
;: (define W2 (make-withdraw 100))
;: (W1 50)
;: (W2 70)
;: (W2 40)
;: (W1 40)

(define (make-account balance password)
  (define (withdraw amount)
    (if (>= balance amount)
        (begin (set! balance (- balance amount))
               balance)
        "Insufficient funds"))
  (define (deposit amount)
    (set! balance (+ balance amount))
    balance)
  (define (dispatch p m)
    (if (eq? p password)
        (cond ((eq? m 'withdraw) withdraw)
              ((eq? m 'deposit) deposit)
              (else (error "Unknown request -- MAKE-ACCOUNT"
                           m)))
        (lambda (x) 'incorrect-password)))
  dispatch)

(define acc (make-account 100 123))

;: ((acc 'withdraw) 50)
;: ((acc 'withdraw) 60)
;: ((acc 'deposit) 40)
;: ((acc 'withdraw) 60)

;;; rozdział 3.1.3

(define (make-simplified-withdraw balance)
  (lambda (amount)
    (set! balance (- balance amount))
    balance))


;: (define W (make-simplified-withdraw 25))
;: (W 20)
;: (W 10)


(define (make-decrementer balance)
  (lambda (amount)
    (- balance amount)))

;: (define D (make-decrementer 25))
;: (D 20)
;: (D 10)

;: ((make-decrementer 25) 20)
;: ((lambda (amount) (- 25 amount)) 20)
;: (- 25 20)

;: ((make-simplified-withdraw 25) 20)

;: ((lambda (amount) (set! balance (- 25 amount)) 25) 20)
;: (set! balance (- 25 20)) 25

;;; Toższamość obiektów

;: (define D1 (make-decrementer 25))
;: (define D2 (make-decrementer 25))
;: 
;: (define W1 (make-simplified-withdraw 25))
;: (define W2 (make-simplified-withdraw 25))
;: 
;: (W1 20)
;: (W1 20)
;: (W2 20)

;: (define peter-acc (make-account 100))
;: (define paul-acc (make-account 100))
;: 
;: (define peter-acc (make-account 100))
;: (define paul-acc peter-acc)

;;; Kłopoty z programowaniem imperatywnym

(define (factorial n)
  (define (iter product counter)
    (if (> counter n)
        product
        (iter (* counter product)
              (+ counter 1))))
  (iter 1 1))

(define (factorial2 n)
  (let ((product 1)
        (counter 1))
    (define (iter)
      (if (> counter n)
          product
          (begin (set! product (* counter product))
                 (set! counter (+ counter 1))
                 (iter))))
    (iter)))


;; -------------------Kolejki--------------- ;;

(define (front-ptr queue) (mcar queue))
(define (rear-ptr queue) (mcdr queue))
(define (set-front-ptr! queue item) (set-mcar! queue item))
(define (set-rear-ptr! queue item) (set-mcdr! queue item))

(define (empty-queue? queue) (null? (front-ptr queue)))
(define (make-queue) (mcons '() '()))

(define (front-queue queue)
  (if (empty-queue? queue)
      (error "FRONT called with an empty queue" queue)
      (mcar (front-ptr queue))))

(define (insert-queue! queue item)
  (let ((new-pair (mcons item '())))
    (cond ((empty-queue? queue)
           (set-front-ptr! queue new-pair)
           (set-rear-ptr! queue new-pair)
           queue)
          (else
           (set-mcdr! (rear-ptr queue) new-pair)
           (set-rear-ptr! queue new-pair)
           queue))))

(define (delete-queue! queue)
  (cond ((empty-queue? queue)
         (error "DELETE! called with an empty queue" queue))
        (else
         (set-front-ptr! queue (mcdr (front-ptr queue)))
         queue)))

(define (make-cycle xs)
  (define (iter res)
    (if (null? (mcdr res))
        (begin
          (set-mcdr! res xs)
          xs)
        (iter (mcdr res))))
  (if (null? xs)
      (error "pusta")
      (iter xs)))

(define l (make-cycle (mcons 1 (mcons 2 (mcons 3 null)))))

(define lizak (mcons 1 (mcons 2 (mcons 3 (make-cycle (mcons 3 (mcons 3 (mcons 6 null))))))))

(define (has-cycle? xs)
  (define (help ys zs)
    (if (and
         (mpair? ys)
         (and
          (mpair? zs)
          (mpair? (mcdr zs))))
        (let ((w1 (mcdr ys))
              (w2 (mcdr (mcdr zs))))
          (if (equal? w1 w2)
              #t
              (help w1 w2)))
        #f))
  (help xs xs))

(define (make-monitored p)
  (define iter 0)
  (define (how-many?)
    iter)
  (define (reset)
    (set! iter 0)
    iter)
  (define (use-proc . xs)
    (begin (set! iter (+ iter 1)) (apply p xs)))
  (cons use-proc  
        (λ(x) (cond [(eq? x 'how-many?) (how-many?)]
                    [(eq? x 'reset) (reset)]))))

(define c (make-monitored +))

;; --------------------Listy---------------------- ;;
#|
(define (lcons x f)
  (cons x f))

(define (lhead l)
  (car l))

(define (ltail l)
  ((cdr l)))
|#


;; alternatywna implementacja wykorzystująca listy modyfikowalne

(define (lcons x f)
  (mcons x f))

(define (lhead l)
  (mcar l))

(define (ltail l)
  (when (procedure? (mcdr l))
      (set-mcdr! l ((mcdr l))))
  (mcdr l))


(define (ltake n l)
  (if (or (null? l) (= n 0))
      null
      (cons (lhead l)
            (ltake (- n 1) (ltail l)))))

(define (lfilter p l)
  (cond [(null? l) null]
        [(p (lhead l))
         (lcons (lhead l)
                (lambda ()
                  (lfilter p (ltail l))))]
        [else (lfilter p (ltail l))]))

(define (lmap f . ls)
  (if (ormap null? ls) null
      (lcons (apply f (map lhead ls))
             (lambda ()
               (apply lmap (cons f (map ltail ls)))))))

;; ciąg Fibonacciego

(define fib
  (lcons 0
         (lambda ()
           (lcons 1
                  (lambda ()
                    (lmap + fib (ltail fib)))))))


;; silnia

(define fact
  (lcons 1
         (lambda ()
           (lmap * (integers-starting-from 1) fact))))

;; sumy czesciowe

(define (ladd xs)
  (define sum
    (lcons 0
           (lambda ()
             (lmap + sum xs))))
  sum)

;; spamiętywanie

(define (memo-proc proc) 
  (let ((already-run? false) (result false))
    (lambda ()
      (if (not already-run?)
          (begin (set! result (proc))
                 (set! already-run? true)
                 result)
          result))))

;(define (lcons x f)
;  (cons x (memo-proc f)))

(define ones
  (lcons 1
         (lambda ()
           ones)))

;; dodatkowy przykład: liczby pierwsze

(define (integers-starting-from n)
  (lcons n (lambda () (integers-starting-from (+ n 1)))))

(define naturals (integers-starting-from 0))

(define (divisible? x y) (= (remainder x y) 0))
(define no-sevens
  (lfilter (lambda (x) (not (divisible? x 7)))
           naturals))

(define (sieve stream)
  (lcons
   (lhead stream)
   (lambda ()
     (sieve (lfilter
             (lambda (x)
               (not (divisible? x (lhead stream))))
             (ltail stream))))))

(define primes (sieve (integers-starting-from 2)))
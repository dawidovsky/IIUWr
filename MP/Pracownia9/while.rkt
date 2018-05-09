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
;; WHILE
;;

; memory

(define empty-mem
  null)

(define (set-mem x v m)
  (cond [(null? m)
         (list (cons x v))]
        [(eq? x (caar m))
         (cons (cons x v) (cdr m))]
        [else
         (cons (car m) (set-mem x v (cdr m)))]))

(define (get-mem x m)
  (cond [(null? m) 0]
        [(eq? x (caar m)) (cdar m)]
        [else (get-mem x (cdr m))]))

; arith and bools

(define (const? t)
  (number? t))

(define (op? t)
  (and (list? t)
       (> (length t) 0)
       (member (car t) '(+ - * / = > >= < <= %))))

(define (op-op e)
  (car e))

(define (op-args e)
  (cdr e))

(define (op->proc op)
  (cond [(eq? op '+) +]
        [(eq? op '*) *]
        [(eq? op '-) -]
        [(eq? op '/) /]
        [(eq? op '=) =]
        [(eq? op '%) modulo]
        [(eq? op '>) >]
        [(eq? op '>=) >=]
        [(eq? op '<)  <]
        [(eq? op '<=) <=]))

(define (var? t)
  (symbol? t))

(define (eval-arith e m)
  (cond [(var? e) (get-mem e m)]
        [(op? e)
         (apply
          (op->proc (op-op e))
          (map (lambda (x) (eval-arith x m))
               (op-args e)))]
        [(const? e) e]))

;;

(define (assign? t)
  (and (list? t)
       (= (length t) 3)
       (eq? (second t) ':=)))

(define (assign-var e)
  (first e))

(define (assign-expr e)
  (third e))

(define (if? t)
  (tagged-tuple? 'if 4 t))

(define (if-cond e)
  (second e))

(define (if-then e)
  (third e))

(define (if-else e)
  (fourth e))

(define (while? t)
  (tagged-tuple? 'while 3 t))

(define (while-cond t)
  (second t))

(define (while-expr t)
  (third t))

(define (block? t)
  (list? t))

(define (post++? t)
  (and (list? t)
       (= (length t) 2)
       (eq? '++ (second t))
       ))

(define (post-var++ t)
  (first t))

(define (pre++? t)
  (and (list? t)
       (= (length t) 2)
       (eq? '++ (first t))))

(define (pre-var++ t)
  (second t))

(define (for? t)
  (tagged-tuple? 'for 5 t))

(define (for-assign t)
  (second t))

(define (for-cond t)
  (third t))

(define (for-inc t)
  (fourth t))

(define (for-body t)
  (fifth t))

;;

(define (eval e m)
  (cond [(assign? e)
         (set-mem
          (assign-var e)
          (eval-arith (assign-expr e) m)
          m)]
        [(if? e)
         (if (eval-arith (if-cond e) m)
             (eval (if-then e) m)
             (eval (if-else e) m))]
        [(while? e)
         (if (eval-arith (while-cond e) m)
             (eval e (eval (while-expr e) m))
             m)]
        [(for? e)
         (eval (list (for-assign e)
                     (list 'while (for-cond e) (list (for-body e) (for-inc e)))) m)]
        [(post++? e)
         (set-mem
          (post-var++ e)
          (+ (get-mem (post-var++ e) m) 1)
          m)]
        [(pre++? e)
         (set-mem
          (pre-var++ e)
          (+ (get-mem (pre-var++ e) m) 1)
          m)]
        [(block? e)
         (if (null? e)
             m
             (eval (cdr e) (eval (car e) m)))]))

(define (run e)
  (eval e empty-mem))

;;

(define fact10
  '( (i := 10)
     (r := 1)
     (while (> i 0)
            ( (r := (* i r))
              (i := (- i 1)) ))))

(define (computeFact10)
  (run fact10))

(define (fib n)
  `( (i := ,n)
     (f1 := 0)
     (f2 := 1)
     (while (> i 0)
            ((temp := f2)
             (f2 := (+ f1 f2))
             (f1 := temp)
             (i := (- i 1))))))

(define (computefib n)
  (run (fib n)))

(define (prime n)
  `( (n := ,n)
     (i := 2)
     (sum := 0)
     (while (> n 0)
            ((divs := 0)
             (j := 2)
             (while (<= (* j j) i)
                    ((if (= (% i j) 0)
                         (divs := (+ divs 1))
                         '())
                     (j := (+ j 1)))
                    (if (> divs 0)
                        '()
                        (sum := (+ sum i))
                        (n := (- n 1))
                        (i := (+ i 1))))))))

(define (primes n)
  (run (prime n)))

;; (run '( (while := 5)
;;         (while (> while -1)
;;                 ( (while := (- while 1))))))
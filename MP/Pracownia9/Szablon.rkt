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

; arith and bool expressions: syntax and semantics

(define (const? t)
  (number? t))

(define (true? t)
  (eq? t 'true))

(define (false? t)
  (eq? t 'false))

(define (op? t)
  (and (list? t)
       (member (car t) '(+ - * / = > >= < <= not and or mod rand))))

(define (op-op e)
  (car e))

(define (op-args e)
  (cdr e))

(define (op->proc op m)
  (cond [(eq? op '+) +]
        [(eq? op '*) *]
        [(eq? op '-) -]
        [(eq? op '/) /]
        [(eq? op '=) =]
        [(eq? op '>) >]
        [(eq? op '>=) >=]
        [(eq? op '<)  <]
        [(eq? op '<=) <=]
        [(eq? op 'not) not]
        [(eq? op 'and) (lambda x (andmap identity x))]
        [(eq? op 'or) (lambda x (ormap identity x))]
        [(eq? op 'mod) modulo]
        [(eq? op 'rand)  (lambda (max) (var-after-rand
                                        ((rand max)(get-mem 'seed m))))])) ; chosen by fair dice roll.
; guaranteed to be random.

(define (var? t)
  (symbol? t))

(define (eval-arith e m)
  (cond [(true? e) true]
        [(false? e) false]
        [(var? e) (get-mem e m)]
        [(op? e)
         (apply
          (op->proc (op-op e) m)
          (map (lambda (x) (eval-arith x (set-mem 'seed (+ 42 (get-mem 'seed m)) m)))
               (op-args e)))]
        [(const? e) e]))

;; syntax of commands

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

;; state

(define (res v s)
  (cons v s))

(define (res-val r)
  (car r))

(define (res-state r)
  (cdr r))

;; psedo-random generator

(define initial-seed
  123456789)

(define (rand max)
  (lambda (i)
    (let ([v (modulo (+ (* 1103515245 i) 12345) (expt 2 32))])
      (res (modulo v max) v))))

;; ############################################################
;; selektor do rand i jego wartości po obliczeniu
(define (rand-expr e)
  (second e))

(define (var-after-rand e)
  (car e))

;; WHILE interpreter

(define (old-eval e m)
  (cond [(assign? e)
         (set-mem
          (assign-var e)
          (eval-arith (assign-expr e) m)
          m)]
        [(if? e)
         (if (eval-arith (if-cond e) m)
             (old-eval (if-then e) m)
             (old-eval (if-else e) m))]
        [(while? e)
         (if (eval-arith (while-cond e) m)
             (old-eval e (old-eval (while-expr e) m))
             m)]
        [(block? e)
         (if (null? e)
             m
             (old-eval (cdr e) (old-eval (car e) m)))]))

;; ##########################################################################
;; oblczenia zaczynam z pamięcią zawierającą ziarno
;; jeżeli natrafiam na "rand" przy przypisaniu to przypisuje zmiennej
;; wynik naszego rand'a i zwiększam nasze ziarno o 42
;; dlatego kolejne wywołania rand'a z tą samą wartością maksymalną
;; dają różne wyniki 
(define (eval e m seed)
  (define (eval-e e m)
    (cond [(assign? e)
           (set-mem
            (assign-var e)
            (let ((a-s (assign-expr e)))
              (if (eq? (and (list? a-s)(op-op a-s)) 'rand)
                  (var-after-rand ((rand (eval-arith (rand-expr a-s) m))
                                   (get-mem 'seed m)))
                  (eval-arith a-s m)))
            (set-mem 'seed (+ 42 (get-mem 'seed m)) m))]
          [(if? e)
           (if (eval-arith (if-cond e) m)
               (eval-e (if-then e) m)
               (eval-e (if-else e) m))]
          [(while? e)
           (if (eval-arith (while-cond e) m)
               (eval-e e (eval-e (while-expr e) m))
               m)]
          [(block? e)
           (if (null? e)
               m
               (eval-e (cdr e) (eval-e (car e) m)))]))
  (eval-e e (set-mem 'seed seed m)))

(define (run e)
  (eval e empty-mem initial-seed))

;; ###########################################################################

(define fermat-test
  '((composite := false)
    (pot := 0)
    (while (> k 0)
         ((los := (+ 2(rand (- n 2))))
          (pot := los)
          (i := (- n 1))
          (while (> i 1)
                 ((los := (* pot los))
                  (i := (- i 1))))
           (if (= (mod los n) 1)
               (k := (- k 1))
              ( composite := true ))))))
  
  ;; TODO : ZAD A: Zdefiniuj reprezentację programu w jęzku
  ;;        WHILE, który wykonuje test Fermata, zgodnie z
  ;;        treścią zadania. Program powinien zakładać, że
  ;;        uruchamiany jest w pamięci, w której zmiennej
  ;;        n przypisana jest liczba, którą testujemy, a
  ;;        zmiennej k przypisana jest liczba iteracji do
  ;;        wykonania. Wynik powinien być zapisany w
  ;;        zmiennej comopsite. Wartość true oznacza, że
  ;;        liczba jest złożona, a wartość false, że jest
  ;;        ona prawdopodobnie pierwsza.

(define (probably-prime? n k) ; check if a number n is prime using
  ; k iterations of Fermat's primality
  ; test
  (let ([memory (set-mem 'k k
                         (set-mem 'n n empty-mem))])
    (not (get-mem
          'composite
          (eval fermat-test memory initial-seed)))))

;; TESTY

(run '(( x := (rand 20))
       ( y := (rand 20))
       ( z := (rand 20))
       ( w := (rand 20))
       ( a := (rand 20))))

(run '(( x := (+ 42 (rand 20)))
       ( y := (+ 42 (rand 20)))
       ( z := (+ 42 (rand 20)))
       ( w := (+ 42 (rand 20)))
       ( a := (+ 42 (rand 20)))))
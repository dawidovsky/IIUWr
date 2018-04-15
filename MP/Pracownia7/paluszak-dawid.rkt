#lang racket

;; ##################################################################
;; ## WSPÓLNA PRACA - Dawid Paluszak , Szymon Miler, Patryk Wilusz ##
;; ##################################################################

;; expressions

(define (const? t)
  (number? t))

(define (op? t)
  (and (list? t)
       (member (car t) '(+ - * /))))

(define (op-op e)
  (car e))

(define (op-args e)
  (cdr e))

(define (op-cons op args)
  (cons op args))

(define (op->proc op)
  (cond [(eq? op '+) +]
        [(eq? op '*) *]
        [(eq? op '-) -]
        [(eq? op '/) /]))

(define (let-def? t)
  (and (list? t)
       (= (length t) 2)
       (symbol? (car t))))

(define (let-def-var e)
  (car e))

(define (let-def-expr e)
  (cadr e))

(define (let-def-cons x e)
  (list x e))

(define (let? t)
  (and (list? t)
       (= (length t) 3)
       (eq? (car t) 'let)
       (let-def? (cadr t))))

(define (let-def e)
  (cadr e))

(define (let-expr e)
  (caddr e))

(define (let-cons def e)
  (list 'let def e))

(define (var? t)
  (symbol? t))

(define (var-var e)
  e)

(define (var-cons x)
  x)

(define (arith/let-expr? t)
  (or (const? t)
      (and (op? t)
           (andmap arith/let-expr? (op-args t)))
      (and (let? t)
           (arith/let-expr? (let-expr t))
           (arith/let-expr? (let-def-expr (let-def t))))
      (var? t)))

;; let-lifted expressions

(define (arith-expr? t)
  (or (const? t)
      (and (op? t)
           (andmap arith-expr? (op-args t)))
      (var? t)))

(define (let-lifted-expr? t)
  (or (and (let? t)
           (let-lifted-expr? (let-expr t))
           (arith-expr? (let-def-expr (let-def t))))
      (arith-expr? t)))

;; generating a symbol using a counter

(define (number->symbol i)
  (string->symbol (string-append "x" (number->string i))))

;; environments (could be useful for something)

(define empty-env
  null)

(define (add-to-env x v env)
  (cons (list x v) env))

(define (find-in-env x env)
  (cond [(null? env) (error "undefined variable" x)]
        [(eq? x (caar env)) (cadar env)]
        [else (find-in-env x (cdr env))]))

;;struktura i selektory naszej reprezentacji let-lift
(define (let-lift-cons lets-list exprs) ;;
  (list 'let-lift lets-list exprs))

(define (let-lift-lets struct)
  (second struct))

(define (let-lift-exprs struct)
  (third struct))

;; struktura i selektory naszej reprezentacji let-lift z iteratorem

(define (SI-cons struct iter)
  (cons struct iter))

(define (SI-let-lift struct)
  (car struct))

(define (SI-iter struct)
  (cdr struct))

;; procedura łączy listę letów i usuwa z niej nulle
(define (let-lift-concat structs)
  (remove-nulls (concatMap (map let-lift-lets structs))))

;; procedura usuwająca nulle z list
(define (remove-nulls s) 
  (filter-map (lambda (a) (if (null? a) #f a)) s))

(define (concatMap list)
  (define (concat res acc)
    (if (null? res)
        acc
        (concat (cdr res) (append acc (car res)))))
  (concat list null))

;; procedura map z iteratorem  
(define (map-with-iterator proc l i)
  (define (iter res x acc)
    (if (null? res)
        (cons acc x)
        (let ((returned (proc (car res) x)))
          (iter (cdr res) (cdr returned) (cons (car returned) acc)))))
  (let ((returned (iter l i null)))
    (cons (reverse (car returned)) (cdr returned))))

(define (let-lift e)
  (define (let-lift-iter res env i)
    (cond [(const? res) (SI-cons (let-lift-cons '() res) i)]
          [(var? res) (SI-cons (let-lift-cons '() (find-in-env res env)) i)]
          [(op? res)
           ;; SI-op-args - struktura z iteratorem zawierająca wszystkie przemianowane argumenty operatora
           ;; let-lift-op-args - przemianowane argumenty
           ;; lets-def-from-op-args - przemianowane let-definicje z argumentów
           ;; expressions - przemianowane wyrażenia z argumentów
           (let* ((SI-op-args (map-with-iterator (lambda (a b) (let-lift-iter a env b)) (op-args res) i))
                  (let-lift-op-args (SI-let-lift SI-op-args))
                  (lets-def-from-op-args (let-lift-concat let-lift-op-args))
                  (expressions (map let-lift-exprs let-lift-op-args)))
             ;; tworzenie struktury z iteratorem
             ;; pierwszy argument - struktura let-lift z definicjami letów i wyrażeniami(z operatorem)
             ;; drugi argument - iterator
             (SI-cons (let-lift-cons lets-def-from-op-args (cons (op-op res) expressions)) (SI-iter SI-op-args)))]
          [(let? res)
           ;; var-from-let-def - wyrażenie wyciągnietę z definicji let'a
           ;; fresh-var - generowanie świeżej zmiennej
           ;; SI-def-expr - struktura z iteratorem przemianowanego wyrażenia z let-definicji
           ;; expr-from-def - przemianowane wyrażenie z let-definicji
           ;; new-env - powiązanie śweżej zmiennej ze zmienną z let-definicji
           ;; SI-expr - struktura z iteratorem przemionawego wyrażenia z let'a
           ;; expressions - przemianowane wyrażenia
           ;; lets - (wynikowy let) - lety z wyrażenia let-definicji, aktualny let-def ze świeżą zmienną
           ;; i lety z wyrażenia let'a
           (let* ([var-from-let-def (let-def-var (let-def res))]
                  [fresh-var (number->symbol (+ 1 i))]
                  [SI-def-expr (let-lift-iter (let-def-expr (let-def res)) env (+ i 1))]
                  [expr-from-def (SI-let-lift SI-def-expr)]
                  [new-env (add-to-env var-from-let-def fresh-var env)]
                  [SI-expr (let-lift-iter (let-expr res) new-env (SI-iter SI-def-expr))]
                  [expressions (SI-let-lift SI-expr)]
                  [lets (remove-nulls (concatMap (list (let-lift-lets expr-from-def)
                                                       (list (let-def-cons fresh-var (let-lift-exprs expr-from-def)))
                                                       (let-lift-lets expressions))))])
             ;; tworzenie struktury z iteratorem
             ;; pierwszy argument - struktura let-lift z definicjami letów i 
             ;; wyrażeniem z let'a
             ;; drugi argument - iterator                                  
             (SI-cons (let-lift-cons lets
                                  (let-lift-exprs expressions)) (SI-iter SI-expr)))]))
  
  (let-lift->let (SI-let-lift (let-lift-iter e empty-env 0))))

;; procedura zmieniająca naszą reprezentację let-lift na
;; let wyrazenie z wykładu, ale z wyciągniętymi letami
(define (let-lift->let x)
  (define (change-help res)
    (if (null? res)
        (let-lift-exprs x)
        (let-cons (car res) (change-help (cdr res)))))
  (change-help (let-lift-lets x)))

;; ewaluator służący do porównywania wyników i testowania (z wykładu)
(define (eval-env e env)
  (cond [(const? e) e]
        [(op? e)
         (apply (op->proc (op-op e))
                (map (lambda (a) (eval-env a env))
                     (op-args e)))]
        [(let? e)
         (eval-env (let-expr e)
                   (env-for-let (let-def e) env))]
        [(var? e) (find-in-env (var-var e) env)]))

(define (env-for-let def env)
  (add-to-env
   (let-def-var def)
   (eval-env (let-def-expr def) env)
   env))

(define (eval e)
  (eval-env e empty-env))

;; testy 

(define test1 (let-lift '(+ (let (x 3) (+ 3 x)) (let (x 2) (+ 3 x)) (* 2 3) 5)))
(define test2 (let-lift '(+ 10 (* ( let ( x 7) (+ x 2) ) 2) )))
(define test3 (let-lift '( let ( x (- 2 ( let ( z 3) z ) ) ) (+ x 2))))
(define test4 (let-lift '(let (x 3) (+ x (let (z 2) z)))))
(define test5 (let-lift '(+ (let (x 3) (* x (let (x 8) (+ x x)))) (let (y 2) (+ y (+ 2 4 6 (* 3 2 4)))))))
(define test7 (let-lift '(let (x 4) (+ 3 2))))
(define test8 (let-lift '(+ (let (x 3) (+ 1 x)) (let (x 4) (+ 1 x)))))
(define test9 (let-lift '(+ (+ 3 4) (* 2 4))))
(define test10 (let-lift '(+ (let (x (let (y 4) (+ y 4))) (+ 3 x)) (let (x (let (y 4) (+ y 4))) (+ 3 x)))))

(define (test)
  (let* ((expr1 '(+ (let (x 3) (+ 3 x)) (let (x 2) (+ 3 x)) (* 2 3) 5))
         (expr2 '(+ 10 (* (let (x 7) (+ x 2)) 2)))
         (expr3 '(let (x (- 2 (let (z 3) z))) (+ x 2)))
         (expr4 '(let (x 3) (+ x (let (z 2) z))))
         (expr5 '(+ (let (x 3) (* x (let (x 8) (+ x x)))) (let (y 2) (+ y (+ 2 4 6 (* 3 2 4))))))
         (expr6 '(let (x 4) (+ 3 2)))
         (expr7 '(+ (let (x 3) (+ 1 x)) (let (x 4) (+ 1 x))))
         (expr8 '(+ (+ 3 4) (* 2 4)))
         (expr9 '(+ (let (x (let (y 4) (+ y 4))) (+ 3 x)) (let (x (let (y 4) (+ y 4))) (+ 3 x)))))
         
  (let ((tests(list test1 test2 test3 test4
                    test5 test7 test8
                    test9 test10))
        (tests2(list expr1 expr2 expr3
                     expr4 expr5 expr6
                     expr7 expr8 expr9)))
    
    (display "Czy przemianowane lety spełniają predykat let-lifted-expr?\n")
    (display (map (lambda (a) (let-lifted-expr?  a)) tests))
    (newline)
    
    (display "Czy dają te same wyniki?\n")
    (let ((toplevellet-list (map (lambda (x) (eval x)) tests))
          (let-list (map (lambda (y) (eval y)) tests2)))
      
    (display toplevellet-list)
    (newline)
    (display let-list)
    (newline)
    (equal? toplevellet-list let-list)))))
    
(test)

;; ##################################################################
;; ## WSPÓLNA PRACA - Dawid Paluszak , Szymon Miler, Patryk Wilusz ##
;; ##################################################################

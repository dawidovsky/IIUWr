#lang racket

(define (const? t)
  (number? t))

(define (binop? t)
  (and (list? t)
       (= (length t) 3)
       (member (car t) '(+ - * /))))

(define (binop-op e)
  (car e))

(define (binop-left e)
  (cadr e))

(define (binop-right e)
  (caddr e))

(define (binop-cons op l r)
  (list op l r))

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

(define (hole? t)
  (eq? t 'hole))

(define (arith/let/holes? t)
  (or (hole? t)
      (const? t)
      (and (binop? t)
           (arith/let/holes? (binop-left  t))
           (arith/let/holes? (binop-right t)))
      (and (let? t)
           (arith/let/holes? (let-expr t))
           (arith/let/holes? (let-def-expr (let-def t))))
      (var? t)))

(define (num-of-holes t)
  (cond [(hole? t) 1]
        [(const? t) 0]
        [(binop? t)
         (+ (num-of-holes (binop-left  t))
            (num-of-holes (binop-right t)))]
        [(let? t)
         (+ (num-of-holes (let-expr t))
            (num-of-holes (let-def-expr (let-def t))))]
        [(var? t) 0]))

(define (arith/let/hole-expr? t)
  (and (arith/let/holes? t)
       (= (num-of-holes t) 1)))

;; pomocnicza procedura zawiera listę wynikową i let-wyrażenie
;; jeżeli natrafimy na symbol 'hole to zwracamy listę wynikową
;; jeżeli natrafimy na let? i 'hole nie występuje w definicja let'a
;; to dodajemy zmienną która jest w definicji do listy wynikowej
;; jeżeli hole występuje w definicja leta to zwracamy listę wynikową
;; jeżeli natrafimy na wyrażenie binop? to wywołujemy procedurę na
;; binop-left i binop-right
(define (hole-context e)
  (define (hole-list xs res)
    (if (arith/let/hole-expr? e)
        (cond [(eq? 'hole res) (remove-duplicates xs)]
              [(let? res)
               (if (member 'hole (let-def res))
                   (remove-duplicates xs)
                   (hole-list
                    (cons (let-def-var (let-def res)) xs)
                    (let-expr res)))]
              [(binop? res)
               (if (arith/let/hole-expr? (binop-left res))
                   (hole-list xs (binop-left res))
                   (hole-list xs (binop-right res)))])
        (error "Bledne wyrazenie")))
  (hole-list '() e))

;; sortowanie z poprzedniej pracowni sortujące po symbolach
(define (var<? x y)
  (symbol<? x y))

;; testy przechowujemy w tests, gdzie tests to lista dwuelementowych list
;; gdzie pierwszym elementem podlisty jest hole-wyrażenie, a drugim spodziewany wynik
;; otrzymany wynik jak i spodziewany sortuję procedurą z poprzedniej pracowni
;; by uniknąć sprzeczności w porównywaniu list
;; w przypadku przejścia wszystkich testów zwracane jest #t
;; wpp zwracamy hole-wyrażenie, które zwraca fałszywy wynik,
;; wynik jaki zwróciło hole-context oraz wynik spodziewany
 (define (test)
  (define tests
    (list (list '(+ 3 hole) '())
          (list '(let(x 3) (let(y 7) (+ x hole))) '(y x))
          (list '(let(x 3) (let(y hole) (+ x 3))) '(x))
          (list '(let(x hole) (let(y 7) (+ x 3))) '())
          (list '(let (piesek 1)(let(kotek 7)(let(piesek 9)(let(chomik 5) hole)))) '(chomik kotek piesek))
          (list '(+ (let (x 4) 5) hole) '())
          ))
  (define (check xs)
  (cond [(null? xs) #t]
        [(equal? (sort (cadar xs) var<?) (sort (hole-context (caar xs)) var<?))
         (check (cdr xs))]
        [else
         (display "Bledne rozwiazanie w tescie: \n")
         (display (caar xs))
         (display "\n Otrzymano: \n")
         (display (sort (hole-context (caar xs)) var<?))
         (display "\nPowinno być:\n")
         (display (sort (cadar xs) var<?))]))
  (check tests))
         
        
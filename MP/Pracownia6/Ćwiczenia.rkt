#lang racket

;; arithmetic expressions

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

(define (arith-expr? t)
  (or (const? t)
      (and (binop? t)
           (arith-expr? (binop-left  t))
           (arith-expr? (binop-right t)))))

;; calculator

(define (op->proc op)
  (cond [(eq? op '+) +]
        [(eq? op '*) *]
        [(eq? op '-) -]
        [(eq? op '/) /]))

(define (eval-arith e)
  (cond [(const? e) e]
        [(binop? e)
         ((op->proc (binop-op e))
            (eval-arith (binop-left  e))
            (eval-arith (binop-right e)))]))

;; let expressions

(define (let-def? t)
  (and (list? t)
       (= (length t) 2)
       (symbol? (car t))))

(define (let-defs? t)
  (and (list? t) (andmap let-def? t)))

(define (let-defs e) (cadr e))
(define (let-def e) (car e))

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
       (let-defs? (cadr t))))

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
      (and (binop? t)
           (arith/let-expr? (binop-left  t))
           (arith/let-expr? (binop-right t)))
      (and (let? t)
           (arith/let-expr? (let-expr t))
           (arith/let-expr? (let-defs (let-def-expr t))))
      (and (if-zero? t)
           (arith/let-expr? (if-zero-if t))
           (arith/let-expr? (if-zero-true t))
           (arith/let-expr? (if-zero-false t)))
      (var? t)))

;; evalation via substitution

(define (subst e x f)
  (cond [(const? e) e]
        [(binop? e)
         (binop-cons
           (binop-op e)
           (subst (binop-left  e) x f)
           (subst (binop-right e) x f))]
        [(let? e)
         (let-cons
           (let-def-cons
             (let-def-var (let-defs e))
             (subst (let-def-expr (let-defs e)) x f))
           (if (eq? x (let-def-var (let-defs e)))
               (let-expr e)
               (subst (let-expr e) x f)))]
        [(var? e)
         (if (eq? x (var-var e))
             f
             (var-var e))]))

(define (eval-subst e)
  (cond [(const? e) e]
        [(binop? e)
         ((op->proc (binop-op e))
            (eval-subst (binop-left  e))
            (eval-subst (binop-right e)))]
        [(let? e)
         (eval-subst
           (subst
             (let-expr e)
             (let-def-var (let-defs e))
             (eval-subst (let-def-expr (let-defs e)))))]
        [(var? e)
         (error "undefined variable" (var-var e))]))

;; evaluation via environments

(define empty-env
  null)

(define (add-to-env x v env)
  (cons (list x v) env))

(define (find-in-env x env)
  (cond [(null? env) (error "undefined variable" x)]
        [(eq? x (caar env)) (cadar env)]
        [else (find-in-env x (cdr env))]))

(define (eval-env e env)
  (cond [(const? e) e]
        [(binop? e)
         ((op->proc (binop-op e))
            (eval-env (binop-left  e) env)
            (eval-env (binop-right e) env))]
        [(if-zero? e) (if (= 0 (eval-env (if-zero-if e) env))
                          (eval-env (if-zero-true e) env)
                          (eval-env (if-zero-false e) env))]
        [(oper? e) (apply (op->proc (oper-op e)) (map (lambda (a) (eval-env a env)) (oper-arg e)))]
        [(let? e)
         (eval-env
           (let-expr e)
           (eval-let (let-defs e) env))]
        [(var? e) (find-in-env (var-var e) env)]))

(define (eval-let dfs env)
  (define (f def gl-env)
    (if (null? def)
        gl-env
        (f (cdr def) (add-to-env (let-def-var (let-def def))
                                 (eval-env (let-def-expr (let-def def)) env)
                                           gl-env))))
  (append (f dfs empty-env) env))

(define (env-for-let def env)
  (add-to-env
    (let-def-var def)
    (eval-env (let-def-expr def) env)
    env))

(define (eval e)
  (eval-env e empty-env))


;; cwiczenia
;;bez flattena
(define (arith->rpn e)
  (define (rec e acc)
    (cond [(const? e) (cons e acc)]
          [(binop? e) (rec (binop-left e) (rec (binop-right e) (cons (binop-op e) acc)))]
          [else (error " ")]))
  (rec e null))
          
;; flatten

(define (arith-to-rpn e)
  (define (ar->rpn exp)
    (cond [(const? exp) (list exp)]
          [(binop? exp) (list (ar->rpn (binop-left exp))
                              (ar->rpn (binop-right exp))
                              (binop-op exp))]))
    (flatten (ar->rpn e)))


(define empty-stack null)

(define push cons)
                                     
(define (pop s) s)

(define (stack? s)
  (or (null? s)
      (and (const? (car s))
           (stack? (cdr s)))))

;; (provided (all-defined-out))
;; (require "stack.rkt")

(define (op? x)
  (member x '(+ - * /)))

(define (eval-rpn e)
  (define (helper exp valstack)
    (cond [(null? exp) (car (pop valstack))]
          [(number? (car exp)) (helper (cdr exp) (push (car exp) valstack))]
          [(op? (car exp))
                (let ((a (car (pop valstack)))
                      (b (car (pop (cdr (pop valstack))))))
                  (helper (cdr exp) (push ((op->proc (car exp)) b a)
                                          (cdr (pop (cdr (pop valstack)))))))]))
  (helper e empty-stack))
                  
(define a '(+ 2 (* 2 3)))
(define b (arith->rpn a))
;; (eval-rpn b)

(define (if-zero? e)
  (and (list? e)
       (= 4 (length e))
       (eq? (car e) 'if-zero)))

(define if-zero-if second)
(define if-zero-true third)
(define if-zero-false fourth)

;; (eval '(if-zero  (- 2 3) (/ 1 0) 9))

(define (oper? t)
  (and (list? t)
;;       (> (length t) 0)
       (op? (car t))))

(define (oper-op t) (car t))
(define (oper-arg t) (cdr t))

(define (oper-cons op args) (cons op args))

(define (arith/let/oper-expr? t)
  (or (const? t)
      (and (oper? t)
           (andmap (arith/let/oper-expr? (oper-arg t))))
      (and (let? t)
           (arith/let/oper-expr? (let-expr t))
           (arith/let/oper-expr? (let-defs (let-def-expr t))))
      (var? t)))

(define n '(+ 1 2 3 (* 1 2 3)))
;;(eval n)

(define s '(let ((x 1) (y 2)) (+ x y)))
;;(eval s)

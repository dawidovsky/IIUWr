#lang racket

;; expressions

(define (const? t)
  (number? t))

(define (op? t)
  (and (list? t)
       (member (car t) '(+ - * / > < >= <= =))))

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
        [(eq? op '/) /]
        [(eq? op '=) =]
        [(eq? op '>) >]
        [(eq? op '<) <]
        [(eq? op '<=) <=]
        [(eq? op '>=) >=]))
        

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

;; set

(define empty-set
  (identity null))

(define (add-to-set x s)
  (cond [(null? s) (list x)]
        [(eq? x (car s)) s]
        [else (cons (car s) (add-to-set x (cdr s)))]))

(define (merge-sets s1 s2)
  (cond [(null? s1) s2]
        [else (add-to-set (car s1) (merge-sets (cdr s1) s2))]))

(define (set-member? x s)
  (member x s))
  
(define (set->list s)
  (identity s))

;; free-variables

(define (fv e env)
  (cond [(const? e) empty-set]
        [(op? e) (args-fv (op-args e) env)]
        [(let? e) (merge-sets
                    (fv (let-def-expr (let-def e)) env)
                    (fv (let-expr e)
                        (add-to-set (let-def-var (let-def e))
                                    env)))]
        [(var? e) (if (set-member? (var-var e) env)
                      empty-set
                      (add-to-set (var-var e) empty-set))]))

(define (args-fv xs env)
  (cond [(null? xs) empty-set]
        [else (merge-sets (fv (car xs) env)
                          (args-fv (cdr xs) env))]))

(define (free-vars e)
  (set->list (fv e empty-set)))

;; pairs

(define (cons? t)
  (and (list? t)
       (= (length t) 3)
       (eq? (car t) 'cons)))

(define (cons-fst e)
  (second e))

(define (cons-snd e)
  (third e))

(define (cons-cons e1 e2)
  (list 'cons e1 e2))

(define (car? t)
  (and (list? t)
       (= (length t) 2)
       (eq? (car t) 'car)))

(define (car-expr e)
  (second e))

(define (cdr? t)
  (and (list? t)
       (= (length t) 2)
       (eq? (car t) 'cdr)))

(define (cdr-expr e)
  (second e))

(define (exp-pair-pred? e)
  (and (list? e)
       (= (length e) 2)
       (eq? 'pair? (car e))))

(define (exp-pair-expr e)
  (second e))

;; lambdas

(define (lambda? t)
  (and (list? t)
       (= (length t) 3)
       (eq? (car t) 'lambda)
       (list? (cadr t))
       (andmap symbol? (cadr t))))

(define (lambda-vars e)
  (cadr e))

(define (lambda-expr e)
  (caddr e))

;; applications

(define (app? t)
  (and (list? t)
       (> (length t) 0)))

(define (app-proc e)
  (car e))

(define (app-args e)
  (cdr e))

;; expressions

(define (expr? t)
  (or (const? t)
      (exp-bool? t)
      (and (op? t)
           (andmap expr? (op-args t)))
      (and (let? t)
           (expr? (let-expr t))
           (expr? (let-def-expr (let-def t))))
      (var? t)
      (and (cons? t)
           (expr? (cons-fst t))
           (expr? (cons-snd t)))
      (and (car? t)
           (expr? (car-expr t)))
      (and (cdr? t)
           (expr? (cdr-expr t)))
      (and (lambda? t)
           (expr? (lambda-expr t)))
      (exp-null? t)
      (and (exp-null-pred? t)
           (expr? (exp-null-expr t)))
      (and (exp-pair-pred? t)
           (expr? (exp-pair-expr t)))
      (and (if-pred? t)
           (expr? (if-if t))
           (expr? (if-true t))
           (expr? (if-false t)))
      (and (app? t)
           (expr? (app-proc t))
           (andmap expr? (app-args t)))
      ))

;; environments

(define empty-env
  null)

(define (add-to-env x v env)
  (cons (list x v) env))

(define (find-in-env x env)
  (cond [(null? env) (error "undefined variable" x)]
        [(eq? x (caar env)) (cadar env)]
        [else (find-in-env x (cdr env))]))

;; closures

(define (closure-cons xs expr env)
  (list 'closure xs expr env))

(define (closure? c)
  (and (list? c)
       (= (length c) 4)
       (eq? (car c) 'closure)))

(define (closure-vars c)
  (cadr c))

(define (closure-expr c)
  (caddr c))

(define (closure-env c)
  (cadddr c))

;; null

(define (exp-null? e)
  (eq? e 'null))

(define (exp-null-pred? e)
  (and (list? e)
       (= 2 (length e))
       (eq? 'null? (car e))))

(define (null-pair-cons e)
  (list 'null? e))

(define (exp-null-expr e)
  (second e))

(define (expr-null-cons) 'null)

;; list

(define (expr-list? e)
  (and (list? e)
       (> (length e) 0)
       (eq? 'list (car e))))

(define expr-list-args cdr)

(define (expr-list->cons e)
  (if (null? e)
      (expr-null-cons)
      (cons-cons (car e) (expr-list->cons (cdr e)))))

;; bools

(define (exp-bool? e)
  (boolean? e))

;; and

(define (and-pred? e)
  (and (list? e)
       (> 0 (length e))
       (eq? 'and (car e))))

;; or

(define (and-pred? e)
  (and (list? e)
       (> 0 (length e))
       (eq? 'or (car e))))

;; if

(define (if-pred? e)
  (and (list? e)
       (= (length e) 4)
       (eq? (car e) 'if)))

(define (if-if e)
  (second e))

(define (if-true e)
  (third e))

(define (if-false e)
  (fourth e))

;; evaluator

(define (eval-env e env)
  (cond [(const? e) e]
        [(exp-bool? e) e]
        [(exp-null? e) null]
        [(exp-pair-pred? e) (pair? (eval-env (exp-pair-expr e) env))]
        [(exp-null-pred? e) (null? (eval-env (exp-null-expr e) env))]
        [(op? e)
         (apply (op->proc (op-op e))
                (map (lambda (a) (eval-env a env))
                     (op-args e)))]
        [(let? e)
         (eval-env (let-expr e)
                   (env-for-let (let-def e) env))]
        [(var? e) (find-in-env (var-var e) env)]
        [(cons? e)
         (cons (eval-env (cons-fst e) env)
               (eval-env (cons-snd e) env))]
        [(expr-list? e)
         (eval-env (expr-list->cons (expr-list-args e)) env)]
        [(car? e)
         (car (eval-env (car-expr e) env))]
        [(cdr? e)
         (cdr (eval-env (cdr-expr e) env))]
        [(lambda? e)
         (closure-cons (lambda-vars e) (lambda-expr e) env)]
        [(if-pred? e)
         (if (eval-env (if-if e) env)
             (eval-env (if-true e) env)
             (eval-env (if-false e) env))]
        [(app? e)
         (apply-closure
           (eval-env (app-proc e) env)
           (map (lambda (a) (eval-env a env))
                (app-args e)))]
        ))

(define (apply-closure c args)
  (eval-env (closure-expr c)
            (env-for-closure
              (closure-vars c)
              args
              (closure-env c))))

(define (env-for-closure xs vs env)
  (cond [(and (null? xs) (null? vs)) env]
        [(and (not (null? xs)) (not (null? vs)))
         (add-to-env
           (car xs)
           (car vs)
           (env-for-closure (cdr xs) (cdr vs) env))]
        [else (error "arity mismatch")]))

(define (env-for-let def env)
  (add-to-env
    (let-def-var def)
    (eval-env (let-def-expr def) env)
    env))

(define (eval e)
  (eval-env e empty-env))
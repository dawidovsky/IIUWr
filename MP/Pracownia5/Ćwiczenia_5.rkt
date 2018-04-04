#lang racket

(define (var? t)
  (symbol? t))

(define (neg? t)
  (and
   (list? t)
   (= 2 (length t))
   (eq? 'neg (car t))))

(define (conj? t)
  (and
   (list? t)
   (= 3 (length t))
   (eq? 'conj (car t))))

(define (disj? t)
  (and
   (list? t)
   (= 3 (length t))
   (eq?'disj (car t))))

(define (prop? f)
(or (var? f)
    (and (neg? f)
         (prop? (neg-subf f)))
    (and(disj? f)
        (prop? (disj-left f))
        (prop? (disj-rght f)))
    (and(conj? f)
        (prop? (conj-left f))
        (prop? (conj-rght f)))))

(define (neg x)
  (list 'neg x))

(define (conj x y)
  (list 'conj x y))

(define (disj x y)
  (list 'disj x y))

(define (neg-subf f)
  (cadr f))

(define (disj-left f)
  (cadr f))

(define (disj-rght f)
  (caddr f))

(define (conj-left f)
  (cadr f))

(define (conj-rght f)
  (caddr f))

(define formula (conj (conj 'p 'q) (disj 'p 'q)))

(define (free-vars form)
  (define (helper res lis)
    (cond [(neg? res) (helper (neg-subf res) lis)]
          [(disj? res) (helper (disj-rght res)
                                (helper (disj-left res) lis))]
          [(conj? res) (helper (conj-rght res)
                                (helper (conj-left res) lis))]
          [else (remove-duplicates (append lis (list res)))]))
  (helper form '()))

(define (gen-vals  xs)
  (if (null? xs)
      (list  null)
      (let*
          ((vss   (gen-vals (cdr xs)))
           (x     (car xs))
           (vst   (map(lambda(vs) (cons (list x true)   vs)) vss))
           (vsf   (map(lambda(vs) (cons (list x false) vs)) vss)))
        (append  vst  vsf))))

(define fo (gen-vals (list 'a 'b)))
(define var-false (list (list 'p #t) (list 'q #f)))
(define var-true (list (list 'p #t) (list 'q #t)))

(define (eval-formula f val)
  (define (find x r)
    (if (null? r)
        (error "Brak rozwiazania")
        (if (eq? x (caar r))
            (cadar r)
            (find x (cdr r)))))
  (cond [(var? f) (find f val)]
        [(neg? f) (not (eval-formula (neg-subf f) val))]
        [(disj? f) (or (eval-formula (disj-left f) val)
                         (eval-formula (disj-rght f) val))]
        [(conj? f) (and (eval-formula (conj-left f) val)
                         (eval-formula (conj-rght f) val))]))

(define (falsifiable-eval? f)
  (define (iter vals)
    (if (null? vals)
        false
        (if (eval-formula f (car vals))
            (iter (cdr vals))
            (car vals))))
    (iter (gen-vals (free-vars f))))
        
(define (literal p)
  (if (or (var? p)
          (and (neg? p) (var? (neg-subf p))))
      (list 'literal p)
      (error "Blad")))

(define (literal? p)
  (and (list? p)
       (= (length p) 2)
       (eq? (car p) 'literal)
       (or (var? (second p))
           (and (neg? p)
                (var? (neg-subf p))))))

(define form (conj (neg 'p) (disj 'p (neg 'q))))

(define (nnf? f)
  (cond [(literal? f) #t]
        [(conj? f) (and (nnf? (conj-left f))
                        (nnf? (conj-rght f)))]
        [(disj? f) (and (nnf? (disj-left f))
                         (nnf? (disj-rght f)))]
        [(neg? f) #f]
        [else (error "Zla formula")]))

(define (convert-to-nnf f)
  (cond [(var? f) (literal f)]
        [(conj? f) (conj (convert-to-nnf (conj-left f))
                         (convert-to-nnf (conj-rght f)))]
        [(disj? f) (disj (convert-to-nnf (disj-left f))
                         (convert-to-nnf (disj-rght f)))]
        [(neg? f) (convert-to-nnf-neg (neg-subf f))]))

(define (convert-to-nnf-neg pf)
  (cond [(var? pf) (literal (neg pf))]
        [(disj? pf) (disj (convert-to-nnf (disj-left pf))
                    (convert-to-nnf (disj-rght pf)))]
        [(conj? pf) (conj (convert-to-nnf (conj-left pf))
                    (convert-to-nnf (conj-rght pf)))]
        [(neg? pf) (convert-to-nnf (neg-subf pf))]))

(define form2-neg (convert-to-nnf form))

(define (make-cl xs)
  (cons 'cl xs))

(define (cl? xs)
  (if (and (pair? xs)
           (eq? (car xs) 'cs)
           (list? (cdr xs))
           (andmap literal? (cdr xs)))
      #t
      #f))

(define (cnf? f)
  (if (and (pair? f)
           (eq? 'cnf (car f))
           (andmap cl? (cdr f)))
      #t
      #f))

(define (make-cnf f)
  (cons 'cnf f))

(define (join xss yss)
  (apply append (map (lambda (p)
         (map (lambda (q) (append (cdr p) (cdr q))) yss)
         xss)))) 

(define (convert-to-cnf f);;nie trybi
  (cond [(literal? f) (make-cnf (list (make-cl (list f))))]
        [(conj? f) (append (convert-to-cnf (conj-left f))
                           (cdr (convert-to-cnf (conj-rght f))))]
        [(disj? f) (make-cnf (join (cdr (convert-to-cnf (disj-left f))) (cdr (convert-to-cnf (disj-rght f)))))]))   
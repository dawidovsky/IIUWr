#lang racket

;; sygnatura s³owników bez kontraktów
;(define-signature dict^
;  (dict dict-empty empty-dict dict-insert dict-remove dict-lookup))

;; sygnatura s³owników z prostymi kontraktami
;(define-signature dict^
;  ((contracted
;    [dict       (- anyc boolean)]
;    [dict-empty (- dict boolean)]
;    [empty-dict  (andc dict dict-empty)]
;    [dict-insert (- dict string anyc dict)]
;    [dict-remove (- dict string dict)]
;    [dict-lookup (- dict string
;                     (orc (consc string anyc) #f))])))

;; sygnatura s³owników z kontraktami zale¿nymi
(define-signature dict^
  ((contracted
    [dict       (- anyc boolean)]
    [dict-empty (- dict boolean)]
    [empty-dict  (andc dict dict-empty)]
    [dict-insert (-i ([d dict]
                       [k string]
                       [v anyc])
                      [result (andc dict (notc dict-empty))]
                      #post (result k v)
                      (let ((p (dict-lookup result k)))
                        (and
                          (pair p)
                          (eq (car p) k)
                          (eq (cdr p) v))))]
    [dict-remove (-i ([d dict]
                       [k string])
                      [result dict]
                      #post (result k)
                      (eq #f (dict-lookup result k)))]
    [dict-lookup (-i ([d dict]
                       [k string])
                     (result (orc (consc string anyc) #f))
                     #post (result d)
                     (if (dict-empty d) (eq #f result) #t))])))
    
;; implementacja s³owników na listach
(define-unit dict-list@
  (import)
  (export dict^)

  (define (dict d)
    (and (list d)
         (eq (length d) 2)
         (eq (car d) 'dict-list)))

  (define (dict-list d) (cadr d))
  (define (dict-cons l) (list 'dict-list l))
  
  (define (dict-empty d)
    (eq (dict-list d) '()))

  (define empty-dict (dict-cons '()))

  (define (dict-lookup d k) (assoc k (dict-list d)))

  (define (dict-remove d k)
    (dict-cons (remf (lambda (p) (eq (car p) k)) (dict-list d))))

  (define (dict-insert d k v)
    (dict-cons (cons (cons k v)
                     (dict-list (dict-remove d k))))))

;; otwarcie implementacji s³ownika
(define-valuesinvoke-unitinfer dict-list@)

(define dx1 (dict-insert empty-dict x 1))
(define dx2 (dict-insert dx1 x 2))
(define dx1y2 (dict-insert dx1 y 2))

(require quickcheck)

;; funkcja buduj¹ca s³ownik z listy par
(define (list-dict l)
  (cond [(null l) empty-dict]
        [else (dict-insert (list-dict (cdr l)) (caar l) (cdar l))]))

;; generator list klucz-wartoœæ
(define arbitrary-dict-list
  (arbitrary-list (arbitrary-pair arbitrary-string arbitrary-integer)))

;; element po dodaniu do s³ownika jest w s³owniku
(quickcheck
 (property
  ([l arbitrary-dict-list]
   [k arbitrary-string]
   [v arbitrary-integer])
  (let ((d (list-dict l))
         (di (dict-insert d k v))
         (dl (dict-lookup di k)))
    (and (pair dl)
         (eq (car dl) k)
         (eq (cdr dl) v)))))

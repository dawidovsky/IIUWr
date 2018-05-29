#lang racket

;; #################################################################
;; ######## Współpraca Zofia Kochutek z Dawid Paluszak #############
;; #################################################################

;; sygnatura: grafy
(define-signature graph^
  ((contracted
    [graph        (-> list? (listof edge?) graph?)]
    [graph?       (-> any/c boolean?)]
    [graph-nodes  (-> graph? list?)]
    [graph-edges  (-> graph? (listof edge?))]
    [edge         (-> any/c any/c edge?)]
    [edge?        (-> any/c boolean?)]
    [edge-start   (-> edge? any/c)]
    [edge-end     (-> edge? any/c)]
    [has-node?    (-> graph? any/c boolean?)]
    [outnodes     (-> graph? any/c list?)]
    [remove-node  (-> graph? any/c graph?)]
    )))

;; prosta implementacja grafów
(define-unit simple-graph@
  (import)
  (export graph^)

  (define (graph? g)
    (and (list? g)
         (eq? (length g) 3)
         (eq? (car g) 'graph)))

  (define (edge? e)
    (and (list? e)
         (eq? (length e) 3)
         (eq? (car e) 'edge)))

  (define (graph-nodes g) (cadr g))

  (define (graph-edges g) (caddr g))

  (define (graph n e) (list 'graph n e))

  (define (edge n1 n2) (list 'edge n1 n2))

  (define (edge-start e) (cadr e))

  (define (edge-end e) (caddr e))

  (define (has-node? g n) (not (not (member n (graph-nodes g)))))
  
  (define (outnodes g n)
    (filter-map
     (lambda (e)
       (and (eq? (edge-start e) n)
            (edge-end e)))
     (graph-edges g)))

  (define (remove-node g n)
    (graph
     (remove n (graph-nodes g))
     (filter
      (lambda (e)
        (not (eq? (edge-start e) n)))
      (graph-edges g)))))

;; sygnatura dla struktury danych
(define-signature bag^
  ((contracted
    [bag?       (-> any/c boolean?)]
    [bag-empty? (-> bag? boolean?)]
    [empty-bag  (and/c bag? bag-empty?)]
    [bag-insert (-> bag? any/c (and/c bag? (not/c bag-empty?)))]
    [bag-peek   (-> (and/c bag? (not/c bag-empty?)) any/c)]
    [bag-remove (-> (and/c bag? (not/c bag-empty?)) bag?)])))

;; struktura danych - stos
(define-unit bag-stack@
  (import)
  (export bag^)
  
  (define (bag? s)
    (list? s))
  
  (define (bag-empty? s)
    (null? s))
  
  (define empty-bag null)
  
  (define (bag-insert s elem)
    (cons elem s))
  
  (define (bag-peek s)
    (car s))
  
  (define (bag-remove s)
    (cdr s)))


;; struktura danych - kolejka FIFO
;; do zaimplementowania przez studentów

(define-unit bag-fifo@
  (import)
  (export bag^)

  ;; selektory i konstruktor
  
  (define (make-fifo in out)
    (cons in out))
  
  (define (fifo-in f)
    (car f))
  
  (define (fifo-out f)
    (cdr f))

  ;; implementacja kolejki
  
  (define (bag? f)
    (and (pair? f)
         (list? (car f))
         (list? (cdr f))))
  
  (define (bag-empty? f)
    (and (pair? f)
         (null? (car f))
         (null? (cdr f))))
  
  (define empty-bag (cons null null))
  
  (define (bag-insert f elem)
    (make-fifo (cons elem (fifo-in f)) (fifo-out f)))
  
  (define (bag-remove f)
    (if (null? (fifo-out f))
        (make-fifo null (cdr (reverse (fifo-in f))))
        (make-fifo (fifo-in f) (cdr (fifo-out f)))))
  
  (define (bag-peek f)
    (if (null? (fifo-out f))
        (car (reverse (fifo-in f)))
        (car (fifo-out f)))))
 

;; sygnatura dla przeszukiwania grafu
(define-signature graph-search^
  (search))

;; implementacja przeszukiwania grafu
;; uzależniona od implementacji grafu i struktury danych
(define-unit/contract graph-search@
  (import bag^ graph^)
  (export (graph-search^
           [search (-> graph? any/c (listof any/c))]))
  (define (search g n)
    (define (it g b l)
      (cond
        [(bag-empty? b) (reverse l)]
        [(has-node? g (bag-peek b))
         (it (remove-node g (bag-peek b))
             (foldl
              (lambda (n1 b1) (bag-insert b1 n1))
              (bag-remove b)
              (outnodes g (bag-peek b)))
             (cons (bag-peek b) l))]
        [else (it g (bag-remove b) l)]))
    (it g (bag-insert empty-bag n) '()))
  )

;; otwarcie komponentu grafu
(define-values/invoke-unit/infer simple-graph@)

;; graf testowy
(define test-graph
  (graph
   (list 1 2 3 4)
   (list (edge 1 3)
         (edge 1 2)
         (edge 2 4))))

(define my-graph1
  (graph
   (list 1 2 3 4 5)
   (list (edge 1 2)
         (edge 2 3)
         (edge 3 4)
         (edge 4 5))))

(define my-graph2
  (graph
   (list 1 2 3 4 5)
   (list (edge 1 2)
         (edge 2 1)
         (edge 3 4)
         (edge 4 3)
         (edge 5 1))))

(define my-graph3
  (graph
   (list 1 2 3)
   (list (edge 1 2)
         (edge 2 1)
         (edge 2 3)
         (edge 3 2))))
;; TODO: napisz inne testowe grafy!

;; otwarcie komponentu stosu
(define-values/invoke-unit/infer bag-stack@)
;; opcja 2: otwarcie komponentu kolejki
;(define-values/invoke-unit/infer bag-fifo@)

;; testy w Quickchecku
(require quickcheck)

;; test przykładowy: jeśli do pustej struktury dodamy element
;; i od razu go usuniemy, wynikowa struktura jest pusta
(quickcheck
 (property ([s arbitrary-symbol])
           (bag-empty? (bag-remove (bag-insert empty-bag s)))))

;; czy pusty jest pusty
(quickcheck
 (bag-empty? empty-bag))

;; sprawdzenie czy jeśli dodamy jeden elemenet to będzie on tym wyjściowym
(quickcheck
 (property ([s arbitrary-symbol])
           (equal? s (bag-peek (bag-insert empty-bag s)))))

;; testy dla stosu

;; test inserta i peek
;; dodajemy 3 elementy i sprawdzamy czy pierwszy będzie pierwszym wyjętym
;(quickcheck
; (property ([s1 arbitrary-symbol]
;            [s2 arbitrary-symbol]
;            [s3 arbitrary-symbol])
;           (equal? s1 (bag-peek (bag-insert (bag-insert (bag-insert empty-bag s3) s2) s1)))))

;; test remove
;; dodajemy 4 elementy, usuwamy jeden i sprawdzamy czy drugi
;; dodany będzie pierwszym wyjętym
;(quickcheck
; (property ([s1 arbitrary-symbol]
;            [s2 arbitrary-symbol]
;            [s3 arbitrary-symbol]
;            [s4 arbitrary-symbol])
;           (equal? s2 (bag-peek (bag-remove (bag-insert (bag-insert (bag-insert (bag-insert empty-bag s4) s3) s2) s1))))))

; testy dla kolejki

;; test inserta i peek
;; dodajemy 3 elementy i sprawdzamy czy ostatni będzie pierwszym wyjętym
;(quickcheck
; (property ([s1 arbitrary-symbol]
;            [s2 arbitrary-symbol]
;            [s3 arbitrary-symbol])
;           (equal? s3 (bag-peek (bag-insert (bag-insert (bag-insert empty-bag s3) s2) s1)))))

;; test remove
;; dodajemy 4 elementy, usuwamy jeden i sprawdzamy czy przedostatni
;; dodany będzie pierwszym wyjętym
;(quickcheck
; (property ([s1 arbitrary-symbol]
;            [s2 arbitrary-symbol]
;            [s3 arbitrary-symbol]
;            [s4 arbitrary-symbol])
;           (equal? s3 (bag-peek (bag-remove (bag-insert (bag-insert (bag-insert (bag-insert empty-bag s4) s3) s2) s1))))))

;; TODO: napisz inne własności do sprawdzenia!
;; jeśli jakaś własność dotyczy tylko stosu lub tylko kolejki,
;; wykomentuj ją i opisz to w komentarzu powyżej własności

;; otwarcie komponentu przeszukiwania
(define-values/invoke-unit/infer graph-search@)

;; uruchomienie przeszukiwania na przykładowym grafie
;(search test-graph 1)
(newline)(display "Moje testy na grafach")(newline)
(display "Powinno dać cały graf (1 2 3 4 5), ponieważ 1 jest pierwszym wierzchołkiem.")
(display " Graf 1->2->3->4->5 Szukamy 1")(newline)
(search my-graph1 1)
(newline)
(display "Powinno dać tylko 5 , ponieważ 5 jest ostatnim wierzchołkiem.")
(display " Graf 1->2->3->4->5 Szukamy 5")(newline)
(search my-graph1 5)
(newline)
(display "Powinno dać (1 2), ponieważ 1 łączy się tylko z 2, a dwójka z jedynką.")
(display " Graf 5->1<->2 3<->4 Szukamy 1")(newline)
(search my-graph2 1)
(newline)
(display "Powinno dać (3 4), ponieważ 3 łączy się tylko z 4, a czwórka z trójką.")
(display " Graf 5->1<->2 3<->4 Szukamy 3")(newline)
(search my-graph2 3)
(newline)
(display "Powinno dać (5 1 2), ponieważ 5 łączy się z 1, a jedynka tylko z 2 i dwójka znów z 1.")
(display " Graf 5->1<->2 3<->4 Szukamy 5")(newline)
(search my-graph2 5)
(newline)
(display "Powinno dać (), ponieważ 6 nie jest w tym grafie.")
(display " Graf 5->1<->2 3<->4 Szukamy 6")(newline)
(search my-graph2 6)
(newline)
(display "Powinno dać (1 2 3), ponieważ wszystkie wierzchołki łączą się między sobą.")
(display " Graf 1<->2<->3 Szukamy 1")(newline)
(search my-graph3 1)
(newline)
(display "Powinno dać (2 3 1), ponieważ wszystkie wierzchołki łączą się między sobą.")
(display " Graf 1<->2<->3 Szukamy 2")(newline)
(search my-graph3 2)
(newline)
(display "Powinno dać (3 2 1), ponieważ wszystkie wierzchołki łączą się między sobą.")
(display " Graf 1<->2<->3 Szukamy 3")(newline)
(search my-graph3 3)
(newline)
;; TODO: uruchom przeszukiwanie na swoich przykładowych grafach!

;; #################################################################
;; ######## Współpraca Zofia Kochutek z Dawid Paluszak #############
;; #################################################################

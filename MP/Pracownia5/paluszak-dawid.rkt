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

;; reprezentacja danych wejściowych (z ćwiczeń)
(define (var? x)
  (symbol? x))

(define (var x)
  x)

(define (var-name x)
  x)

;; przydatne predykaty na zmiennych
(define (var<? x y)
  (symbol<? x y))

(define (var=? x y)
  (eq? x y))

(define (literal? x)
  (and (tagged-tuple? 'literal 3 x)
       (boolean? (cadr x))
       (var? (caddr x))))

(define (literal pol x)
  (list 'literal pol x))

(define (literal-pol x)
  (cadr x))

(define (literal-var x)
  (caddr x))

(define (clause? x)
  (and (tagged-list? 'clause x)
       (andmap literal? (cdr x))))

(define (clause . lits)
  (cons 'clause lits))

(define (clause-lits c)
  (cdr c))

(define (cnf? x)
  (and (tagged-list? 'cnf x)
       (andmap clause? (cdr x))))

(define (cnf . cs)
    (cons 'cnf cs))

(define (cnf-clauses x)
  (cdr x))

;; oblicza wartość formuły w CNF z częściowym wartościowaniem. jeśli zmienna nie jest
;; zwartościowana, literał jest uznawany za fałszywy.
(define (valuate-partial val form)
  (define (val-lit l)
    (let ((r (assoc (literal-var l) val)))
      (cond
       [(not r)  false]
       [(cadr r) (literal-pol l)]
       [else     (not (literal-pol l))])))
  (define (val-clause c)
    (ormap val-lit (clause-lits c)))
  (andmap val-clause (cnf-clauses form)))

;; reprezentacja dowodów sprzeczności

(define (axiom? p)
  (tagged-tuple? 'axiom 2 p))

(define (proof-axiom c)
  (list 'axiom c))

(define (axiom-clause p)
  (cadr p))

(define (res? p)
  (tagged-tuple? 'resolve 4 p))

(define (proof-res x pp pn)
  (list 'resolve x pp pn))

(define (res-var p)
  (cadr p))

(define (res-proof-pos p)
  (caddr p))

(define (res-proof-neg p)
  (cadddr p))

;; sprawdza strukturę, ale nie poprawność dowodu
(define (proof? p)
  (or (and (axiom? p)
           (clause? (axiom-clause p)))
      (and (res? p)
           (var? (res-var p))
           (proof? (res-proof-pos p))
           (proof? (res-proof-neg p)))))

;; procedura sprawdzająca poprawność dowodu
(define (check-proof pf form)
  (define (run-axiom c)
    (displayln (list 'checking 'axiom c))
    (and (member c (cnf-clauses form))
         (clause-lits c)))
  (define (run-res x cpos cneg)
    (displayln (list 'checking 'resolution 'of x 'for cpos 'and cneg))
    (and (findf (lambda (l) (and (literal-pol l)
                                 (eq? x (literal-var l))))
                cpos)
         (findf (lambda (l) (and (not (literal-pol l))
                                 (eq? x (literal-var l))))
                cneg)
         (append (remove* (list (literal true x))  cpos)
                 (remove* (list (literal false x)) cneg))))
  (define (run-proof pf)
    (cond
     [(axiom? pf) (run-axiom (axiom-clause pf))]
     [(res? pf)   (run-res (res-var pf)
                           (run-proof (res-proof-pos pf))
                           (run-proof (res-proof-neg pf)))]
     [else        false]))
  (null? (run-proof pf)))


;; reprezentacja wewnętrzna
;; sprawdza posortowanie w porządku ściśle rosnącym, bez duplikatów
(define (sorted? vs)
  (or (null? vs)
      (null? (cdr vs))
      (and (var<? (car vs) (cadr vs))
           (sorted? (cdr vs)))))

(define (sorted-varlist? x)
  (and (list? x)
       (andmap var? x)
       (sorted? x)))

;; klauzulę reprezentujemy jako parę list — osobno wystąpienia pozytywne i negatywne. Dodatkowo
;; pamiętamy wyprowadzenie tej klauzuli (dowód) i jej rozmiar.
(define (res-clause? x)
  (and (tagged-tuple? 'res-int 5 x)
       (sorted-varlist? (second x))
       (sorted-varlist? (third x))
       (= (fourth x) (+ (length (second x)) (length (third x))))
       (proof? (fifth x))))

(define (res-clause pos neg proof)
  (list 'res-int pos neg (+ (length pos) (length neg)) proof))

(define (res-clause-pos c)
  (second c))

(define (res-clause-neg c)
  (third c))

(define (res-clause-size c)
  (fourth c))

(define (res-clause-proof c)
  (fifth c))

;; przedstawia klauzulę jako parę list zmiennych występujących odpowiednio pozytywnie i negatywnie
(define (print-res-clause c)
  (list (res-clause-pos c) (res-clause-neg c)))

;; sprawdzanie klauzuli sprzecznej
(define (clause-false? c)
  (and (null? (res-clause-pos c))
       (null? (res-clause-neg c))))

;; pomocnicze procedury: scalanie i usuwanie duplikatów z list posortowanych
(define (merge-vars xs ys)
  (cond [(null? xs) ys]
        [(null? ys) xs]
        [(var<? (car xs) (car ys))
         (cons (car xs) (merge-vars (cdr xs) ys))]
        [(var<? (car ys) (car xs))
         (cons (car ys) (merge-vars xs (cdr ys)))]
        [else (cons (car xs) (merge-vars (cdr xs) (cdr ys)))]))

(define (remove-duplicates-vars xs)
  (cond [(null? xs) xs]
        [(null? (cdr xs)) xs]
        [(var=? (car xs) (cadr xs)) (remove-duplicates-vars (cdr xs))]
        [else (cons (car xs) (remove-duplicates-vars (cdr xs)))]))

(define (rev-append xs ys)
  (if (null? xs) ys
      (rev-append (cdr xs) (cons (car xs) ys))))

;; TODO: miejsce na uzupełnienie własnych funkcji pomocniczych

;; liczymy przecięcie i zwracamy listę tych symboli.
(define (intersection c1 c2)
  (define (helper wynik k1 k2)
    (cond [(or (null? k1) (null? k2))
           (if (null? wynik)
               #f
               (sort wynik var<?))]
          [(var=? (car k1) (car k2)) (helper (cons (car k1) wynik) (cdr k1) (cdr k2))]
          [(var<? (car k1) (car k2)) (helper wynik (cdr k1) k2)]
          [(var<? (car k2) (car k1)) (helper wynik k1 (cdr k2))]))
  (helper '() c1 c2))

;; jeśli przecięcie pozytywnych i negatywnych zawiera jakieś elementy
;; to klauzula jest trywialna. 
(define (clause-trivial? c)
  (if (eq? #f (intersection (cadr c) (caddr c)))
      #f
      #t))

;; bierzemy pierwszą zmienną z listy przecięcia i wykonujemy na niej rezolucję
;; najpierw sprawdzamy pozytywne z pierwszej i negatywne z drugiej,
;; jeśli nie da się zrobić tak rezolucji to sprawdzamy
;; później pozytywne z drugiej i negatywne z pierwszej
(define (resolve c1 c2)
  (let ((inter (intersection (cadr c1) (caddr c2))))
    (if (eq? #f inter)
        (let ((inter (intersection (cadr c2) (caddr c1))))
          (if (eq? #f inter)
              #f
              (res-clause (remove (car inter)(merge-vars (cadr c1) (cadr c2)))
                          (remove (car inter)(merge-vars (caddr c1) (caddr c2)))
                          (proof-res (car inter) (fifth c2) (fifth c1)))))
        (res-clause (remove (car inter)(merge-vars (cadr c1) (cadr c2)))
                    (remove (car inter)(merge-vars (caddr c1) (caddr c2)))
                    (proof-res (car (cadr c1)) (fifth c1) (fifth c2))))))

(define (resolve-single-prove s-clause checked pending)
  ;; TODO: zaimplementuj!
  ;; Poniższa implementacja działa w ten sam sposób co dla większych klauzul — łatwo ją poprawić!
  (let* ((resolvents   (filter-map (lambda (c) (resolve c s-clause))
                                     checked))
         (sorted-rs    (sort resolvents < #:key res-clause-size)))
    (subsume-add-prove (cons s-clause checked) pending sorted-rs)))

;; wstawianie klauzuli w posortowaną względem rozmiaru listę klauzul
(define (insert nc ncs)
  (cond
   [(null? ncs)                     (list nc)]
   [(< (res-clause-size nc)
       (res-clause-size (car ncs))) (cons nc ncs)]
   [else                            (cons (car ncs) (insert nc (cdr ncs)))]))

;; sortowanie klauzul względem rozmiaru (funkcja biblioteczna sort)
(define (sort-clauses cs)
  (sort cs < #:key res-clause-size))

;; główna procedura szukająca dowodu sprzeczności
;; zakładamy że w checked i pending nigdy nie ma klauzuli sprzecznej
(define (resolve-prove checked pending)
  (cond
   ;; jeśli lista pending jest pusta, to checked jest zamknięta na rezolucję czyli spełnialna
   [(null? pending) (generate-valuation (sort-clauses checked))]
   ;; jeśli klauzula ma jeden literał, to możemy traktować łatwo i efektywnie ją przetworzyć
   [(= 1 (res-clause-size (car pending)))
    (resolve-single-prove (car pending) checked (cdr pending))]
   ;; w przeciwnym wypadku wykonujemy rezolucję z wszystkimi klauzulami już sprawdzonymi, a
   ;; następnie dodajemy otrzymane klauzule do zbioru i kontynuujemy obliczenia
   [else
    (let* ((next-clause  (car pending))
           (rest-pending (cdr pending))
           (resolvents   (filter-map (lambda (c) (resolve c next-clause))
                                     checked))
           (sorted-rs    (sort-clauses resolvents)))
      (subsume-add-prove (cons next-clause checked) rest-pending sorted-rs))]))


;; zawieranie
(define (containing? xs ys)
  (let ((posx (second xs))
        (posy (second ys))
        (negx (third xs))
        (negy (third ys)))
    (if (and (equal? posx (intersection posx posy))
             (equal? negx (intersection negx negy)))
        #t
        #f)))

;; procedura upraszczająca stan obliczeń biorąc pod uwagę świeżo wygenerowane klauzule i
;; kontynuująca obliczenia. Do uzupełnienia.
(define (subsume-add-prove checked pending new)
  (cond
   [(null? new)                 (resolve-prove checked pending)]
   ;; jeśli klauzula do przetworzenia jest sprzeczna to jej wyprowadzenie jest dowodem sprzeczności
   ;; początkowej formuły
   [(clause-false? (car new))   (list 'unsat (res-clause-proof (car new)))]
   ;; jeśli klauzula jest trywialna to nie ma potrzeby jej przetwarzać
   [(clause-trivial? (car new)) (subsume-add-prove checked pending (cdr new))]
   [(ormap (lambda (x) (containing? (car new) x)) checked)
    (subsume-add-prove checked pending (cdr new))]
   [(ormap (lambda (x) (containing? (car new) x)) pending)
    (subsume-add-prove checked pending (cdr new))]
   [else
    (subsume-add-prove checked (insert (car new) pending) (cdr new))
    ]))

;; usuwanie z wszystkich klauzul w res
;; wszystkich wystąpień vars ( gdzie vars to zmienne które już wystąpiły podczas generowania)
(define (remove-vars vars res)
  (define (new-clau-list vars res new)
    (cond [(null? res) (sort-clauses new)]
          [else (let ((new-cl (res-clause
                               (remq* vars (second (car res)))
                              (remq* vars (third (car res)))
                              (fifth (car res)))))
                  (new-clau-list vars (cdr res) (cons new-cl new)))]))
  (new-clau-list vars res '()))

;; generator wartościowań
;; jeżeli lista klauzul jest nullem zwracamy wartościowanie
;; jeżeli klauzula ma jedną zmienną to wstawiamy ją do
;; listy wartościowań z odpowiednim wartościowaniem i
;; wstawiamy ją również do listy varsToRem
;; jeżeli napotkamy na klauzule, która me więcej zmiennych to
;; jeżeli jest coś na liście varsToRem to usuwamy ze wszystkich pozostałych
;; klauzul wystąpienia tych zmiennych i zerujemy listę varsToRem
;; jeżeli lista varsToRem jest pusta to bierzemy pierwszą zmienną
;; z klauzuli i wstawiamy ją do listy wartościowań i varsToRem
(define (generate-valuation resolved)
  (define (helper varsToRem vars res)
      (cond [(null? res) (list 'sat vars)]
            [(clause-false? (car res)) (helper varsToRem vars(cdr res))]
            [(= 1 (fourth (car res)))
             (if (null? (second (car res)))
                 (helper (cons (car (third (car res))) varsToRem)
                         (cons (list (car (third (car res))) #f) vars)
                         (cdr res))
                 (helper (cons (car (second (car res))) varsToRem)
                         (cons (list (car (second (car res))) #t) vars)
                         (cdr res)))]
            [else (if (null? varsToRem)
                      (if (null? (second (car res)))
                          (helper (cons (car (third (car res))) varsToRem)
                                  (cons (list (car (third (car res))) #f) vars)
                                  (cdr res))
                          (helper (cons (car (second (car res))) varsToRem)
                                  (cons (list (car (second (car res))) #t) vars)
                                  (cdr res)))
                      (helper '() vars
                              (remove-vars varsToRem res)))]))
  (helper '() '() resolved))
          

;; procedura przetwarzające wejściowy CNF na wewnętrzną reprezentację klauzul
(define (form->clauses f)
  (define (conv-clause c)
    (define (aux ls pos neg)
      (cond
       [(null? ls)
        (res-clause (remove-duplicates-vars (sort pos var<?))
                    (remove-duplicates-vars (sort neg var<?))
                    (proof-axiom c))]
       [(literal-pol (car ls))
        (aux (cdr ls)
             (cons (literal-var (car ls)) pos)
             neg)]
       [else
        (aux (cdr ls)
             pos
             (cons (literal-var (car ls)) neg))]))
    (aux (clause-lits c) null null))
  (map conv-clause (cnf-clauses f)))

(define (prove form)
  (let* ((clauses (form->clauses form)))
    (subsume-add-prove '() '() clauses)))

;; procedura testująca: próbuje dowieść sprzeczność formuły i sprawdza czy wygenerowany
;; dowód/waluacja są poprawne. Uwaga: żeby działała dla formuł spełnialnych trzeba umieć wygenerować
;; poprawną waluację.
(define (prove-and-check form)
  (let* ((res (prove form))
         (sat (car res))
         (pf-val (cadr res)))
    (if (eq? sat 'sat)
        (valuate-partial pf-val form)
        (check-proof pf-val form))))

;;; TODO: poniżej wpisz swoje testy

;; literały do testowania
(define p (literal #t 'p))
(define q (literal #t 'q))
(define r (literal #t 'r))
(define o (literal #t 'o))
(define s (literal #t 's))
(define np (literal #f 'p))
(define nq (literal #f 'q))
(define nr (literal #f 'r))
(define no (literal #f 'o))
(define ns (literal #f 's))

;; test rezolucji
(define c2 (cnf (clause p nq)(clause np)))
(define k2 (form->clauses c2))
(display "Testowania rezolucji klauzul :\n")
(clause p nq) (display " i ") (clause np)
(display "\nRezolucja wygląda tak:\n")
(resolve (car k2) (cadr k2))

;; test trywialności
(display "\nTestowania trywialności klauzuli :\n")
(clause p np)
(display "\nWynik:\n")

(define c3 (cnf (clause p np))) ;; trywialna 
(define k3 (form->clauses c3)) ;; trywialna
(clause-trivial? (car k3))

;; test sprzeczności 
(define c (cnf (clause np q) (clause np nr o) (clause nq r) (clause p) (clause no)))
(display "\nDowód sprzeczności formuły:\n")
c
(display "wygląda następująco:\n\n")
(prove-and-check c) ;; dodów sprzeczności formuły

;; testy spełnialnych 

(define c4 (cnf (clause p nq) (clause q r) (clause r o)))
(define k4 (form->clauses c4))
(display "\nTestowania spełnialności klauzul :\n")
c4
(display "\nWartościowanie wygląda następująco:\n\n")
(prove c4)
(display "\nCzy się zgadza?\n")
(prove-and-check c4)


(define c5 (cnf (clause p) (clause q) (clause r)))
(define k5 (form->clauses c5))
(display "\nTestowania spełnialności klauzul :\n")
c5
(display "\nWartościowanie wygląda następująco:\n\n")
(prove c5)
(display "\nCzy się zgadza?\n")
(prove-and-check c5)

(define c6 (cnf (clause p nq) (clause q no) (clause o r)))
(define k6 (form->clauses c6))
(display "\nTestowania spełnialności klauzul :\n")
c6
(display "\nWartościowanie wygląda następująco:\n\n")
(prove c6)
(display "\nCzy się zgadza?\n")
(prove-and-check c6)

;; Bez zadania 3 - tylko subsum w jedną stronę jest zrobiony oraz procedura zawierania
#lang racket

(define (square x) (* x x))

(define (dist x y)
  (abs (- x y)))

(define (close-enough? x y)
   (< (dist x y) 0.00001))
;; An Bn fk są wprost przepisane z ich definicji z zadania 10
;; An_prev Bn_prev są to wyniki z poprzednich wyliczen An Bn
;; An_prev2 Bn_prev2 poprzednie wyniki do An_prev i Bn_prev
;; fk_prev to poprzedni wynik funkcji fk
;; wyliczamy An Bn następnie dzielimy je przez siebie by otrzymać fk
;; przechodzimy również to kolejnych iteracji licznika i mianownika
;; później jeżeli wyniki fk i fk_prev są wystarczająco podobne to
;; wypisujemy wynik w przeciwnym przypadku iteracyjnie wykonujemy
;; tą samą procedurę (uruchamiamy ją z kolejnymi wartościami argumentów
;; tj. An_prev = An , Nn = Nn_next itd.
(define (func licznik mianownik)
  (define (iter Nn Dn An_prev An_prev2 Bn_prev Bn_prev2 fk_prev n)
    (let
        ([An (+ (* Dn An_prev)(* Nn An_prev2))]
         [Bn (+ (* Dn Bn_prev)(* Nn Bn_prev2))]      
         [Nn_next (licznik (+ n 1))]
         [Dn_next (mianownik (+ n 1))])
         (define fk (/ An Bn))
         (if (close-enough? fk_prev fk)
             fk
             (iter Nn_next Dn_next An An_prev Bn Bn_prev fk (+ n 1)))))
  
  (iter (licznik 1) (mianownik 1) 0.0 1.0 1.0 0.0 0.0 1))

(func (lambda (x) 1) (lambda (x) 1)) ;; ćw 6 

(define (arctan x)(func (lambda (i) (if (= i 1) x (square (* (- i 1) x))))
      (lambda (i) (- (* 2 i) 1)))) ;; ćw 8 
;; testy ćw 8 
(arctan 5)
(atan 5)
(arctan 10)
(atan 10)
(arctan -3)
(atan -3)
(arctan 0)
(atan 0)

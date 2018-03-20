#lang racket

(define (dist x y)
  (abs (- x y)))

(define (average x y)
  (/ (+ x y) 2))

(define (square x)
  (* x x))

(define (inc i)
  (+ i 1))

(define (cube n)
  (* n n n))

;; silnia jako procedura rekurencyjna
(define (fact n)
  (if (= n 0)
      1
      (* n (fact (- n 1)))))

;; i jako procedura iteracyjna
(define (fact-iter n i p)
  (if (= n i)
      p
      (fact-iter n (inc i) (* p (inc i)))))

;; równoważność dwóch definicji przez indukcję, wymaga uogólnienia twierdzenia do
;; dla każdego n, jeśli (natural? n) to dla każdego i (= (fact (+ n i)) (fact-iter (+ n i) i (fact i)))

;; rekurencyjna definicja ciągu Fibonacciego: rekurencyjne wywołania mogą się rozgałęziać
(define (fib n)
  (cond [(= n 0) 0]
        [(= n 1) 1]
        [else    (+ (fib (- n 1)) (fib (- n 2)))]))

;; trzy przykłady sumowania ciągów liczbowych
(define (sum-ints s e)
  (if (> s e)
      0
      (+ s (sum-ints (inc s) e))))

(define (sum-cubes s e)
  (if (> s e)
      0
      (+ (cube s) (sum-cubes (inc s) e))))

(define (sum-pi n e)
  (if (> n e)
      0
      (+ (/ 1 (* n (+ n 2))) (sum-pi (+ n 4) e))))

;; ogólna procedura: abstrakcja wyższego rzędu wyrażająca sumowanie wyrazów *pewnego* szeregu
(define sum
  (lambda (term next s e)
    (if (> s e)
        0
        (+ (term s) (sum term next (next s) e)))))

(define (identity x) x)

;; alternatywny zapis ostatniego z szeregów: zamiast sum-pi-next używamy formy lambda — nienazwanej procedury
(define (sum-pi-alt n e)
  (define (sum-pi-term s)
    (/ 1 (* s (+ s 2))))
  (define (sum-pi-next s)
    (+ s 4))
  (sum sum-pi-term (lambda (s) (+ s 4)) n e))


(define (close-enough? x y)
  (< (dist x y) 0.00001))

;; obliczanie (przybliżonego) punktu stałego funkcji f przez iterację, let pozwala uniknąć powtarzania obliczeń
(define (fix-point f x0)
  (let ((x1 (f x0)))
    (if (close-enough? x0 x1)
        x0
        (fix-point f x1))))

;; próba obliczania pierwiastka kwadratowego z x jako punktu stałego funkcji y ↦ x / y zapętla się
;; stosujemy tłumienie z uśrednieniem: procedurę wyższego rzędu zwracającą procedurę jako wynik
(define (average-damp f)
  (lambda (x) (/ (+ x (f x)) 2)))

(define (sqrt-ad x)
  (fix-point (average-damp (lambda (y) (/ x y))) 1.0))

;; obliczanie pochodnej funkcji z definicji przyjmując dx za "odpowiednio małą" wartość (zamiast "prawdziwej" granicy)
(define (deriv f)
  (let ((dx 0.000001))
    (lambda (x) (/ (- (f (+ x dx)) (f x)) dx))))

;; przekształcenie Newtona: x ↦ x - f(x) / f'(x) pozwala obliczyć miejsce zerowe f jako punkt stały tej transformacji
(define (newton-transform f)
  (lambda (x)
    (- x
       (/ (f x)
          ((deriv f) x)))))

(define (newtons-method f x)
  (fix-point (newton-transform f) x))

;; zastosowania
(define pi (newtons-method sin 3))

(define (sqrt-nm x)
  (newtons-method (lambda (y) (- x (square y))) 1.0))

;; możemy wyabstrahować wzorzec widoczny w definicjach sqrt: znaleźć punkt stały pewnej funkcji *przy użyciu* transformacji
;; argumentem fix-point-of-transform jest procedura przetwarzająca procedury w procedury!
(define (fix-point-of-transform transform f x)
  (fix-point (transform f) x))







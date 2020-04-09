# Lista ćwiczeniowa nr 2

### Zadanie 1

  Czy poniższe wyrażenia zawsze obliczą się do prawdy dla dwóch dowolnych wartości zmiennych x i y typu int32_t? Jeśli nie to podaj wartości, które prowadzą do obliczenia fałszu.
  
1.   ``(x > 0) || (x - 1 < 0)``
::: info
Nie, 
dla x=INT_T_MIN war. x>0 oczywiście nie spełniony , a po wykonaniu x-1 otrzymamy x=INT32_T_MAX zatem x-1<0 również nie będzie spełnione
:::
2. ``(x & 7) != 7 || (x << 29 < 0)``
::: info 
Tak,
Pierwszy warunek nie będzie spełniony jedynie gdy ostatnie 3 bity sa zapalone , war nr2 x<<29 przesuwa bity o 29 miejsc zerując wszystkie oprócz trzech ostatnich bitów które teraz są pierwsze dostajemy wiec liczbe ujemna 1110...0 <0
:::
3. ``(x * x) >= 0``
::: info
Nie, dla x=INT32_T_MAX/2 x*x zwróci liczbę ujemną
:::
> Inny kontrprzykład: x = 0b11 (29 zer) 1, wtedy x*x = -INT32_MAX

4.   ``x < 0 || -x <= 0``
::: info
Tak, ponieważ każdą liczbę dodatnią x można poprawnie  zapisać jako -x - wciąż mieści się w zakresie. Dlatego jeśli liczba jest ujemna - pierwsza się wyrażenia jest prawdziwa. Jeśli jest dodatnia to wyrażenie -x jest zawsze mniejsze lub równe 0.
:::
5.   `` x > 0 || -x >= 0``
::: info
Nie. Dla x = INT32_MIN wyrażenie -x jest mniejsze od zera - przekroczenie zakresu
:::
6.   ``(x | -x) >> 31 == -1``
::: info
Nie, dla x = 0 zarówno x jak i -x mają bit znaku równy 0, dlatego po przesunięciu bitowym wyrażenie (x | -x) >> 31 będzie róne 0.
:::
7.   ``((uint32_t)x) >> 3 == ((uint32_t)x)/8``
::: info 
Tak, ponieważ przesunięcie bitowe to to samo co dzielenie dla liczb dodatnich (bez znaku).
:::
8.   ``x >> 3 == x/8``
:::info
Nie, ponieważ dla liczb ujemnych (ze znakiem) presunięcie w prawo spowoduje skopiowanie najbardziej znaczącego bitu na nowe pozycje, np. x = -1. 
:::
9.   ``x + y == (uint32_t)y + (uint32_t)x``
:::info
Tak, ponieważ podczas wykonywania operacji porównania zmienne ze znakiem zostaną zmienione na zmienne bez znaku.

Algorytm dodwania liczb ze znakiem i bez znaku jest taki sam.
:::



### Zadanie 2

Podaj wyrażenie zawierające wyłącznie zmienne x i y, którego
wartością logiczną jest wynik porównania x < y dla liczb (a) bez~znaku (b) ze~znakiem.

Rozwiązanie (takie samo dla uint i int): 

`(((x >> 1) - (y >> 1) - (~x & y & 1)) >> 31) & 1`

Zauważmy, że najprościej jest sprawdzić wynik obliczenia x - y.
Jednak w taki sposób możemy uzyskać overflow. Dlatego naszym rozwiązaniem będzie podzielenie wartości x i y przez 2.

W taki sposób jednak stracimy najmłodzszy bit.

Przypadki do rozpatrzenia:
1) x i y posiada 1 na najmłodszym bicie: nie musimy się przejmować tym przypadkiem bo strata jest ta sama po obu stronach
2) x i y nie posiada 1 na najmłodszym bicie: podzielenie nie powoduje straty.
3) x ma 1 na najmłodszym bicie a y nie: jedyne pytanie mamy podczas sytuacji gdy (x >> 1) - (y >> 1) będzie równe zero ale to nic nie zmienia bo to nadal x > y (więc wynikiem jest zero).
4) y ma 1 na najmłodszym bicie a x nie: dlatego w tej sytuacji odejmujemy (~x & y & 1) (tylko w tej sytuacji da nam to 1). Robimy to, ponieważ ta stracona jedynka mogła przesądzić o tym, że y >= x.

Na końcu wykonujemy >> 31 oraz & 1 by wydobyć wynik.

### Zadanie 3

Podaj fragment kodu, który oblicza funkcję:
$$
 abs(x) = 
  \begin{cases} 
   x & \text{dla } x \geq 0 \\
   -x & \text{dla } x < 0
  \end{cases}
$$
  Skorzystaj z następującej własności: jeśli b jest wartością logiczną,
  to wyrażenie ``b ? x : y`` można przetłumaczyć do ``b * x + !b * y``.
 
```cpp=
int abs(int x){
    int y = x >> 31;
    // 0 gdy x >= 0 i -1 wtw
    return (x^y)-y;
    // liczba nieujemna pozostaje bez zmian (x XOR 0 = x i y = 0)
    // ujemna po operacji XOR ma zamienione wszystkie bity, dodajemy do niej 1
    //     zgodnie z zasadami odwracania liczb w systemie U2.
}
```

### Zadanie 4

Podaj fragment kodu, który oblicza funkcję:
$$
 sign(x) = 
  \begin{cases} 
   -1 & \text{dla } x < 0 \\
   0 & \text{dla } x = 0 \\
   1 & \text{dla } x > 0
  \end{cases}
$$
```cpp=
int sign(int x)
{
    return 1-
    ( (( (x-1) >>31 ) &1) & (1- (x>>31)&1 ) ) //zwroci 1 gdy x=0
    -(( (x>>31)&1) <<1); // 
    ///        odjęcie 1 jeśli liczba jest 0   jeśli mniejsza od 0 odejmij 2 
}
///(((x-1)>>31)&1) zwraca 1 gdy x<=0, sprawdzamy czy po odjęciu 1 liczba jest ujemna
// 
///((x>>31)&1) zwraca 1 gdy liczba jest ujemna (czy pierwszy bit jest zapalony)
///(1-(x>>31)&1)) zwraca 0 gdy x<0 i 1 gdy x>0


int sign2(int x) ///Na bazie Uczty Programistów
{
    return -(-(x>>31)|(-x>>31));
}
```
>  Jeśli x < 0 to: `-(x >> 31)` jest równe 1, 
>  `-x >> 31` jest równe 0 (dla x > INT32_MIN)
>  `-x >> 31` jest równe -1 (dla x == INT32_MIN)
>  Jeśli x > INT32_MIN to całe wyrażenie jest równe -1
>  Jeśli x == INT32_MIN to całe wyrażenie jest równe 
:::danger
Zatem sign2 nie działa dla x == INT32_MIN
:::
Rozwiązanie działające w każdym przypadku:
`(x >> 31) | ((-x >> 31 ) & 1)`

 Poprawność: analiza przypadków.
 
int mask = x >> 31;
return mask | (x != 0);

>Tworzymy maskę, która dla x nieujemnych będzie składać się z samych 0, natomiast dla ujemnych z samych 1.
Prześledźmy 3 przypadki
>- dodatnie:
maska to same 0, x jest różny od 0, orujemy i zwraca nam 1
>- 0:
maska to same 0, 0 nie jest różne od 0, zwracamy 0
>- ujemne:
maska to same 1, x jest różny od 0, orujemy i zwracamy -1



### Zadanie 5

 Uzupełnij ciało funkcji zadeklarowanej poniżej.
 
```cpp=
/* Jeśli suma x+y mieści się w typie int32_t (nie powoduje
 nadmiaru/niedomiaru) zwróć 1, w p.p. 0*/
int tadd_ok(int32_t x, int32_t y);
{
    int a = ((x+y)^x);
    int b = ((x+y)^y);
        
    return (!( ((a&b)>>31)&1))    
}


```



### Zadanie 6

 Uzupełnij ciało funkcji zadeklarowanej poniżej.
```
/* Jeśli x zawiera nieparzystą liczbę jedynek zwróć 1, w p.p. 0 */
 int32_t odd_ones(uint32_t x);
```
XOR nieparzystej liczby jedynek to 1 a parzystej 0. Możemy zastosować technikę z zad. 7 z listy 1 tylko teraz w każdym bloku agregujemy XOR wszystkich liczb z bloku.

```cpp
int32_t odd_ones(uint32_t x) {
    x = (x & 0x55555555) ^ ((x & 0xAAAAAAAA) >> 1);
    x = (x & 0x33333333) ^ ((x & 0xCCCCCCCC) >> 2);
    x = (x & 0x0F0F0F0F) ^ ((x & 0xF0F0F0F0) >> 4);
    x = (x & 0x00FF00FF) ^ ((x & 0xFF00FF00) >> 8);
    x = (x & 0x0000FFFF) ^ ((x & 0xFFFF0000) >> 16);

    return x;
}
```

### Zadanie 7


Standard IEEE 754-2008 definiuje liczby zmiennopozycyjne o szerokości 16-bitów. Oblicz ręcznie $3.984375 \cdot 10^{-1} + 3.4375 \cdot 10^{-1} + 1.771 \cdot 10^{3}$ używając liczb w tym formacie. Zapisz wynik binarnie i dziesiętnie. Czy wynik się zmieni jeśli najpierw wykonamy drugie dodawanie?

UWAGA! Domyślną metodą zaokrąglania w obliczeniach zmiennoprzecinkowych jest *round-to-even*.

0.75:

0.75 (*2) | 1
0.5  (*2) | 1
0 | -

wynik:
0,11


       dziesiętnie              dziesiętnie unormowane     binarnie
    3.984375 * 10^-1^           0.3984375                           0.0110011
    3.4375 * 10^-1^             0.34375                             0.0101100
    1.771 * 10^3^          1771.0                         11011101011.0

3.984375 * 10^-1^ + 3.4375 * 10^-1^ :

normalizujemy postać binarną do 1 na pierwszym miejscu przed przecinkiem:

               1.10011 * 2^-2^
             + 1.01100 * 2^-2^
        =     10.11111 * 2^-2^
musimy znormalizwać do jedynki na pierwszym miejscu:
        
1.011111 * 2^(-1)^
           w postaci dziesiętnej to 0.7421875 
           
mantysa to 0111110000 (uzupełniona zerami do 10 miejsc)
wykładnik -1 kodujemy według e=exp-bias

znak ma 1 bit, exp ma 5 bitów, mantysa 10 bitów dla half precision
            więc bias=2^(k-1)^-1=15
            -1=exp-bias
            -1=exp-15
            exp=14 -> binarnie: 01110
            
kodowanie dodawania w half precision:
            
0 01110 0111110000
            
(3.984375 * 10^-1^ + 3.4375 * 10^-1^)+ 1771.0 :
            
                      0.1011111
           +11011101011.0
           =11011101011.1011111  
           =1.1011101011 1011111 * 2^10^ (spacja w tym miejscu oznacza "koniec naszej mantysy")
zaokrąglam:
            1.1011101100 * 2^10^
            
            kodowanie:
            
            10=exp-15
            exp=25 binarnie -> 11001
            
            wynik:
            0 11001 1011101100
            w postaci dziesiętnej to 1772
            
Czy wynik się zmieni jeśli wykonamy najpierw drugie dodawanie?
            
3.4375 * 10^-1^+ 1771.0 :
            
                      0.0101100
           +11011101011.0
           =11011101011.0101100
           =1.1011101011 0101100 *2^10^
           =1.1011101011 *2^10^
           
kolejne dodawanie:
           3.984375 * 10^-1^ + (3.4375 * 10^-1^+ 1771.0)
           
           1.1011101011* 2^10^
          +0.0110011
          
          ===
           11011101011.0
         +           0.0110011
         = 11011101011.0110011
         normalizacja do 1:
         
         1.1011101011 0110011* 2^10^
zaokrąglenie:
         1.1011101011 * 2^10^
         
Widzimy,że mantysa się zmieni, a więc i wynik.
         w postaci dziesiętnej będzie to 1771.
         
### Zadanie 8

Załóżmy, że zmienne x, f i d są odpowiednio typów int32_t, float i double. Ich wartości są dowolne, ale f i d nie mogą równać się $+\infty$, $-\infty$ lub NaN. Czy każde z poniższych wyrażeń zostanie obliczone do~prawdy? Jeśli nie to podaj wartości zmiennych, dla których wyrażenie zostanie obliczone do~fałszu.

1. ``x == (int32_t)(double) x``
2. ``x == (int32_t)(float) x``
3. ``d == (double)(float) d``
4. ``f == (float)(double) f``
5. ``f == -(-f)``
6. ``1.0 / 2 == 1 / 2.0`` 
7. ``d * d >= 0.0``
8. ``(f + d) - f == d``

Rozwiązanie:
1. Prawda
2. Fałsz: błąd konwersacji typów (ponieważ float ma mniejszą precyzję niż int32_t zamiast float potrzebny jest double)
3. Fałsz: float nie pomieści double
4. Prawda
5. Prawda, w typie float zmiana znaku to tylko zmiana pierwszego bitu wiec wyrazenie zawsze wyliczy sie do prawdy
6. Prawda, tutaj mamy dwa typy, wiec zarówno mianownik jak i licznik zostaną scastowane do float'a przed porównaniem
7. Prawda, nadmiar i niedomiar nie mają wpływu na znak
8. Fałsz, np: f-duże : 1.0e20 i d-małe : 1.0 f+d = 1.0e20 - f = 0.0 != 1.0 <br/> mając dużą wartość jako float nie wystarczy nam precycji by "przechować" małą z double.



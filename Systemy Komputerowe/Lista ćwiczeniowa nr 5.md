# Lista ćwiczeniowa nr 5(czwartek)

### Zadanie 1

Zdefiniuj pojęcie $\textbf{wyrównania danych}$ w pamięci (ang. \emph{data alignment}). Dlaczego dane typów prostych (np. $\verb@short@$, $\verb@int@$, $\verb@double@$) powinny być w pamięci odpowiednio wyrównane? Jaki związek z wyrównywaniem danych mają $\textbf{wypełnienia}$ (ang. \emph{padding}) w danych typu strukturalnego. Odpowiadając na powyższe pytanie podaj przykład struktury, której rozmiar w bajtach (wyliczony przez operator $\verb@sizeof@$) jest większy niż suma rozmiaru pól składowych.  Czemu służy $\textbf{wypełnienie wewnętrzne}$ (ang. \emph{internal padding}) a czemu $\textbf{wypełnienie zewnętrzne}$ (ang. \emph{external padding})?


Wyrównanie danych to sposób ułożenia danych w pamięci tak,
aby były łatwiej dostępne dla procesora.
~~Polega to na umieszczaniu komórek w pamięci niekoniecznie
bezpośrednio po sobie, ale w pewnych odstępach,
aby zawsze wskazujący je adres był wielokrtonością 4 lub 8
(w zależności od architektury). 
~~> [name=Piotr Witkowski] Dane typów prostych (reprezentowalnych w procesorze jako rejestry) o rozmiarze K są w pamięci układane pod adresami będącymi     wielokrotnością K, czyli np. short (int16_t) pod adresami będacymi wielokrotnością 2, int (int32_t) pod wielokrotnością 4, long (inte64_t) pod wielokrotnością 8.
>. Maks wyrównanie to 16 lub 32 bajty (dotyczy rejestrów MMX/SSE/SSE2).



Wypełnienie w danych typu strukturalnego to te odstępy:
wewnętrzne oddziela dane wewnątrz struktury, tak,
aby ułatwić dostęp do pól, a zewnętrzne występuje na końcu
struktury i zapewnia to, że struktura jako całość
zajmuje odpowiedniej wielkości przestrzeń (wielokrotność
rozmiaru największego pola).
Przykad takiej struktury:

```c
struct Padded{
    float f;
    char c;

sizeof(struct Padded) wynosi 8, a nie 5, bo float zajmuje 4 bajty.
```

Inny przykład
```css=
struct tmp {
char c;
/*tu 3 bajty paddingu*/
int i;
/*brak wypełnienia zewnętrznego*/
}

```

Jest sizeof(struct tmp) jest równy 8.

```css=
struct tmp1 {
int i;
/*brak wypełnienia wewnętrznego*/
char c;
/*3 bajty wypełnienia zewnętrznego.*/
}
```
Jest sizeof(struct t  x=3;
    printf("%i\n",x);
  mp1) też jest równy 8. Rozmiar struktktury musi być wielokrotnością rozmiaru największego elementu typu prostego w niej zapamiętanego --- to jest wymagane by pola w tablicach typu strukturalnego były dobrze wyrównane.

### Zadanie 2

  Dana jest funkcja o sygnaturze \Symbol{int16_t you(int8_t index)} i fragmencie kodu podanym poniżej. Funkcja ta została skompilowana z flagą $\verb@-O0@$, a jej kod asemblerowy również jest podany. Nieznana jest natomiast funkcja \Symbol{int16_t set_secret(void)}. Jaki argument należy podać wywołując $\verb@you@$, by odkryć wartość sekretu?
```
int16_t you(int8_t index) {
struct { 
   int16_t tbl[5]; 
   int8_t tmp;
   int16_t secret;
} str;

str.secret = set_secret();
...
return str.tbl[index];
}
```
```
you:    pushq   %rbp
        movq    %rsp, %rbp
        subq    $24, %rsp
        movl    %edi, %eax
        movb    %al, -20(%rbp)
        call    set_secret
        movw    %ax, -2(%rbp)
        ...
        movsbl  -20(%rbp), %eax
        cltq
        movzwl  -14(%rbp,%rax,2), %eax
        leave
        ret
```
Wskazówka:Instrukcja cltq rozszerza rejestr \%eax do \%rax zachowując znak. Pamiętaj, że zadeklarowane zmienne muszą być odpowiednio wyrównane.

Rozwiązanie:

Żeby odkryć wartość secretu trzeba wywołać funkcję you(6). int16_t tbl[5], str.tbl[0-4] - you(0), you(1), you(2), you(3), you(4), int8_t tmp, str.tbl[5] - you(5), int16_t secret, str.tbl[6] - you(6).


### Zadanie 3(2pkty)

Przeczytaj poniższy kod w języku \texttt{C} i odpowiadający mu kod w asemblerze, a~następnie wywnioskuj jakie są wartości stałych \Symbol{A} i \Symbol{B}.
```
typedef struct {
  int32_t x[A][B];
  int64_t y;
} str1;

typedef struct {
  int8_t array[B];
  int32_t t;
  int16_t s[A];
  int64_t u;
} str2;

void set_val(str1 *p, str2 *q) {
  int64_t v1 = q->t;
  int64_t v2 = q->u;
  p->y = v1 + v2;
}
```
```
set_val:
19  movslq 8(%rsi),%rax
20  addq   32(%rsi),%rax
21  movq   %rax,184(%rdi)
  ret
```

Wskazówka:Deklaracja int32\_t x[A][B] powoduje, że x będzie A-elementową tablicą wartości typu int32\_t [B].  Pamiętaj o wyrównaniu pól w strukturach.

```
19      odwołujemy się do str2.t przesuwając wskaźnik z początku structa
        ((%rsi)) o 8 bajtów, więc array[B] musi mieć rozmiar [5B, 8B] 
        (padding)
20      aby dostać się do str2.u musimy przesunąć się o 32 bajty, zatem 
        nasze szukane pole musi znajdować się na 32 bajcie str2. Z tego
        można wywnioskować, że s[A] musi zajmować więcej niż 12B, a 
        maksymalnie 20B
21      str1.y znajduje się na 184 bajcie struktury str1. W takim razie 
        x[A][B] ma rozmiar z zbioru {180B, 184B}


180 <= sizeof(x) <= 184
180 <= 4*(A*B) <= 184
A*B = 45 lub A*B = 46

5 <= sizeof(array) <= 8
5 <= B <= 8

24 < 8 + 4 + sizeof(s) <= 32
12 < 2*A <= 20
6 < A <= 10
7 <= A <= 10 
A = 9, B = 5, A*B = 45
```
Wizualicja podanych struktur(paddingi zawierają potencjalne rozmiary, a strzałki wskazują na rzeczywisty układ elementów w strukturze): https://imgur.com/XoRItKg


### Zadanie 4(2pkty)

Przeczytaj poniższy kod w języku  $\verb@C@$ i odpowiadający mu kod w asemblerze, a~następnie wywnioskuj jaka jest wartość stałej \Symbol{CNT} i jak wygląda definicja struktury \Symbol{a_struct}.
```
typedef struct {
  int32_t first;        //*bp-4
  a_struct a[CNT];      //4-288 max | dodajemy padding 4 bajty między first a tablicą a_struct, więc 8-288
  int32_t last;        //288-292
} b_struct;

void test (int64_t i, b_struct *bp) {
  int32_t n = bp->first + bp->last;
  a_struct *ap = &bp->a[i];
  ap->x[ap->idx] = n;
}
```
```
test:
movl   0x120(%rsi),%ecx        //stąd wiemy, że first leży na adresie 0x120, więc 288
addl   (%rsi),%ecx
leaq   (%rdi,%rdi,4),%rax     // rax=5*i
leaq   (%rsi,%rax,8),%rax     // *bp+40i
movq   0x8(%rax),%rdx         // wyrównanie adresu w celu podzielności przez 8, więc nasza struktura się mieści między 8-288, czyli zajmuje rozmiar 280. wczytuje idx do rdx
movslq %ecx,%rcx
movq   %rcx,0x10(%rax,%rdx,8) //rozmiar idx wynosi 8, bo przesuwamy tu wskaźnik o 0x10 czyli o 16 (na i*40+8 się zaczyna dana struktura), a następnie skaczmey po tablicy x przesuwając wskaźnik o 8 bajtów
retq
```


Wiadomo, że jedynymi polami w strukturze \Symbol{a_struct} są \Symbol{idx} oraz \Symbol{x}, i że obydwa te pola są typu numerycznego ze znakiem.

rozmiar naszej całej tablicy elementów a_struct wynosi 280, rozmiar pojedyńczej struktury 40, więc CNT=280/40=7.

czyli nasza struktura będzie wyglądać następująco:

typedef struct {
  int64_t idx;
  int64_t x[4];
} a_struct;

### Zadanie 5

Zdefiniuj semantykę operatora \Symbol{?:} z języka  $\verb@C@$. Jakie zastosowanie ma poniższa funkcja.
```
int32_t cread(int32_t *xp) {
  return (xp ? *xp : 0);
```
Używając serwisu $\verb@godbolt.org@$ (kompilator $\verb@x86-64 gcc 8.2@$) sprawdź, czy istnieje taki poziom optymalizacji ($\verb@-O0@$, $\verb@-O1@$, $\verb@-O2@$ lub $\verb@-O3@$), że wygenerowany dla $\verb@cread@$ kod asemblerowy nie używa instrukcji skoku. Jeśli nie, to zmodyfikuj funkcję $\verb@cread@$ tak, by jej tłumaczenie na asembler spełniało powyższy warunek.

Wskazówka: Dążysz do wygenerowania kodu używającego instrukcji cmov. Końcowej instrukcji ret nie uważamy w tym zadaniu za instrukcję skoku.

### Rozwiązanie

Kod w zadaniu używa instrukcji skoku niezależnie od poziomu optymalizacji.

Dla kodu:

```cpp
int32_t cread(int32_t *xp) {
  return (xp ? *xp : 0);
}
```

Generuje się poniższy kod w asemblerze (przy poziomie optymalizacji -O1):

```asm
cread:
        movl    $0, %eax
        testq   %rdi, %rdi
        je      .L1 // jump if ZF = 1
        movl    (%rdi), %eax
.L1:
        ret
```


Po poprawce:

```cpp
int32_t cread(int32_t *xp)
{
    int32_t defaultValue = 0;
    return *(xp != NULL ? xp : &defaultValue);
}
```
Przykład wygenerowanego kodu asemblera dla -O1 po poprawkach (nie używa już instrukcji skoku, generuje instrukcję cmove) 

`The CMOVcc instructions doesn't compare the source and destination. It uses the flags from a previous comparison (or other operation that sets the flags) which determines if the move should be done or not.`

```asm
cread:
        movl    $0, -4(%rsp)
        leaq    -4(%rsp), %rax
        testq   %rdi, %rdi // ustawia ZF = 1 jeśli xp = 0
        cmove   %rax, %rdi // przenieś wartość z %rax do %rdi jeśli ZF = 1
        movl    (%rdi), %eax
        ret
```


![](https://i.imgur.com/ghqEJLi.png)



### Zadanie 6

  W języku $\verb@C@$ struktury mogą być zarówno argumentami funkcji, jak i wartościami zwracanymi przez funkcje\footnote{ Konwencja przekazywania/zwracania argumentów takich typów jest częścią ABI: \url{https://github.com/hjl-tools/x86-psABI/wiki/x86-64 psABI-1.0.pdf}, strony 19--25}. Za pomocą serwisu $\verb@godbolt.org@$ zapoznaj się z tłumaczeniem do asemblera funkcji przyjmujących pojedynczy argument każdego z poniższych typów strukturalnych. Następnie zapoznaj się z tłumaczeniem funkcji zwracających wartość każdego z tych typów. Jakie reguły dostrzegasz?
```  
struct first {
int32_t val1;
};
```
```
struct second {
int32_t val2;    
int32_t val1;
};
```
```
struct third {
int32_t val3;    
int32_t val2;    
int32_t val1;
};
```
```
struct fourth {
int32_t val4;    
int32_t val3;    
int32_t val2;    
int32_t val1;
};
```
```
struct fifth {
int16_t val6;
int16_t val5;
int32_t val3;    
int32_t val2;    
int32_t val1;
};
```
```
struct sixth {
int32_t val7;    
int32_t val4;    
int32_t val3;    
int32_t val2;    
int32_t val1;
};
```
```
struct seventh {
int32_t val8[10000];    
int32_t val4;    
int32_t val3;    
int32_t val2;    
int32_t val1;
};
```
Czy przekazywanie/zwracanie dużych struktur funkcjom jest dobrym pomysłem?

```
struct first f1(struct first s){
    return s;
}
f1:
        pushq   %rbp
        movq    %rsp, %rbp
        movl    %edi, -4(%rbp)  # zapis naszego int32_t do stosu
        movl    -4(%rbp), %eax # zapis do %eax które zwracamy
        popq    %rbp
        ret

struct second f2(struct second s){
    return s;
}
f2:
        pushq   %rbp
        movq    %rsp, %rbp
        movq    %rdi, -8(%rbp) # zapis naszych obu wartosci z rdi w jednej ramce stosu
        movq    -8(%rbp), %rax # zapis do %rax który zwracamy
        popq    %rbp
        ret
        
struct third f3(struct third s){
    return s;
}
f3:
        pushq   %rbp
        movq    %rsp, %rbp
        movq    %rdi, %rdx # dwa pola typu int32_t mieszczą się w %rdi
        movl    %esi, %eax # pozostałe w %esi 
        movq    %rdx, -32(%rbp) # zapis na stosie tych dwóch pól (w jednej ramce)
        movl    %eax, -24(%rbp) # zapis w ramce pozostałego pola
        movq    -32(%rbp), %rax # zapis do %rax dwóch pól
        movq    %rax, -12(%rbp) # zapis na stosie
        movl    -24(%rbp), %eax # zapis do %eax pozostałego pola
        movl    %eax, -4(%rbp) # zapis na stosie 
        movq    -12(%rbp), %rax # jako że będziemy wykożystywać %rax i %rdx zapisz 2 pola do %rax
        movl    -4(%rbp), %ecx
        movq    %rcx, %rdx # zapisz pozostałe do %rdx
        popq    %rbp
        ret

Zauważmy że rozmiar fourth wynosi 3*4B = 12B 
więc jest to jeszcze brane jako CLASS INTEGER (wg dokumentacji i obserwacji)

struct fourth f4(struct fourth s){
    return s;
}
f4:
        pushq   %rbp
        movq    %rsp, %rbp
        movq    %rdi, %rax # zapisz 2 pola do %rax
        movq    %rsi, %rcx # zapisz kolejne do %rcx
        movq    %rcx, %rdx # %rdx = %rcx
        movq    %rax, -16(%rbp) # zapis na stosie 2 pierwszych pól
        movq    %rdx, -8(%rbp) # zapis na stosie pozostałych
        movq    -16(%rbp), %rax # odczyt do zwrócenia
        movq    -8(%rbp), %rdx # odczyt do zwrócenia
        popq    %rbp
        ret
Zauważmy że rozmiar fourth wynosi 4*4B = 16B 
więc jest to jeszcze brane jako CLASS INTEGER (wg dokumentacji i obserwacji)

struct fifth f5(struct fifth s){
    return s;
}
f5:
        pushq   %rbp
        movq    %rsp, %rbp
        movq    %rdi, %rax
        movq    %rsi, %rcx
        movq    %rcx, %rdx
        movq    %rax, -16(%rbp)
        movq    %rdx, -8(%rbp)
        movq    -16(%rbp), %rax
        movq    -8(%rbp), %rdx
        popq    %rbp
        ret
        
Zauważmy że rozmiar fourth wynosi 2*2B+3*4B = 16B 
więc jest to jeszcze brane jako CLASS INTEGER (wg dokumentacji i obserwacji)


struct sixth f6(struct sixth s){
    return s;
}
f6:
        pushq   %rbp
        movq    %rsp, %rbp
        movq    %rdi, -8(%rbp) # zapis wskaźnika na strkturę na stosie
        movq    -8(%rbp), %rcx
        movq    16(%rbp), %rax
        movq    24(%rbp), %rdx
        movq    %rax, (%rcx)
        movq    %rdx, 8(%rcx)
        movl    32(%rbp), %eax
        movl    %eax, 16(%rcx)
        movq    -8(%rbp), %rax # zwrot wskaźnika na strkturę na stosie
        popq    %rbp
        ret

Zauważmy że rozmiar struktury to 5*4B więc 20
zatem nie mieścimy się w CLASS INTEGER, zatem jest to CLASS MEMORY
co oznacza, że zapisujemy sobie wskaźnik( na strukturę przechowywaną w
pamięci) na stosie.  
Zwracamy wskaźnik na naszą strukturę umieszczoną w pamięci.

struct seventh f7(struct seventh s){
    return s;
}
f7:
        pushq   %rbp
        movq    %rsp, %rbp
        subq    $16, %rsp
        movq    %rdi, -8(%rbp) # zapis wskaźnika na strkturę na stosie
        movq    -8(%rbp), %rax
        movq    %rax, %rcx
        leaq    16(%rbp), %rax
        movl    $40016, %edx
        movq    %rax, %rsi
        movq    %rcx, %rdi
        call    memcpy # memory copy
        movq    -8(%rbp), %rax # zapis wskaźnika na strkturę na stosie
        leave
        ret        
        
Zauwazmy że przez duży rozmiar struktury nie mieścimy się w CLASS INTEGER,
zatem jest to CLASS MEMORY co oznacza, że zapisujemy sobie wskaźnik
( na strukturę przechowywaną w pamięci) na stosie.  
Zwracamy wskaźnik na naszą strukturę umieszczoną w pamięci.        
Zauważmy że przekazywanie/zwracać dużych struktur funkcjom NIE jest 
dobrym pomysłem ze wzgledu że wywołujemy memorycopy.
```
Jeżeli nasza struktura mieści się w 16B to jest zapisywana do rejestrów %rdi i %rsi. Jako że to class INTEGER to zwracana jest w rejestrach %rax i %rdx
Jeżeli mieści się w 8B to jest na %rdi, w przeciwnym wypadku wymaga 2 rejestrów na zapis.



W przeciwnym wypadku zapisujemy sobie na stosie wskaźnik na pamięć w której zapisana jest nasza struktura. Przy returnie %rax będzie zawierał adres przekazany w rdi.


### Zadanie 7

W poniższej funkcji zmienna $\verb@field@$ jest polem bitowym typu $\verb@int32_t@$ o rozmiarze $\verb@4@$. Jaką wartość wypisze ta funkcja na ekranie i dlaczego?  Co się stanie, gdy zmienimy typ pola $\verb@field@$ na $\verb@uint32_t@$? Na obydwa te pytania odpowiedz analizując tłumaczenia tej funkcji na język asemblera.
```
void set_field(void) {
struct {
  int32_t field : 4;
} s;
  s.field = 10;
  printf("Field value is: %d\n", s.field);
}
```
Wskazówka:Użyj poziomu optymalizacji \Symbol{-O0}. Dla wyższych poziomów optymalizacji kompilator zauważy, że deklaracja zmiennej \Symbol{s} jest niepotrzebna i obliczy wartość wypisywaną przez \Symbol{printf} podczas kompilacji.

### Rozwiązanie

Pole 4 bitowe - czyli wzięcie tylko 4 ostatnich bitów z całej liczby.
To znaczy, że np. w liczbie 11110011 interesuje nas tylko 0011.

10 w zapisie binarnym to 1010.

Jako int:
1010 -> -8+0+2+0=-6

Jako unit:
1010 -> 10

INT
![](https://i.imgur.com/xOhUuyE.png)

UINT
![](https://i.imgur.com/M3n7Rkj.png)


### Zadanie 8

Język $\verb@C@$ dopuszcza deklaracje tablic wielowymiarowych zopuszczonym rozmiarem pierwszego wymiaru. Taka deklaracja może wystąpić w nagłówku funkcji, np. \Symbol{void process(int32_t A[][77], size_t len)}. Nie można natomiast opuszczać rozmiarów innych wymiarów, np. \Symbol{void bad(int32_t A[77][], size_t len)} nie jest poprawną deklaracją. Wyjaśnij, dlaczego tak jest odwołując się do sposobu, w jaki kompilator tłumaczy odwołania do tablic z $\verb@C@$ na asembler.

### Rozwiązanie

Kompilator musi znać wielkość, tablicy aby prawidłowo wyznaczyć adres.
Adres elementu tablicy obliczany jest według wzoru: 
&A[i][j] = X<sub>A</sub> + L(C * i + j),
gdzie L to wielkość typu T w bajtach dla tablicy T A[R][C].
X<sub>A</sub> to początkowy indeks tablicy
Widzimy, że parametr C musi być znany, aby prawidłowo wyliczyć adres komórki tablicy, jest on mnożony
przez indeks pierwszego elementu.Z tego powodu trzeba podać wielkość "zewnętrznej" tablicy


Analogicznie będzie to działało dla tablic "3+D" (większego rozmiaru).
Analogicznie możemy rozważyć sytuację, gdybyśmy chcieli
zadeklarować tablicę bez podania najbardziej wewnętrzego rozmiaru. Wtedy możemy to zrobić, indeksy będą mogły być obliczone. 

Poniżej zostawiam rysunek podglądowy, aby lepiej wyobrazić sobie tablicę dwuwymiarową (pochodzi z podręcznika)

![](https://i.imgur.com/aYvLK55.png)

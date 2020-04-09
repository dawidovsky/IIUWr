# Lista ćwiczeniowa nr 4

### Zadanie 1

Rejestry $\verb@%reg1%@$ i $\verb@%reg2@$ są tego samego rozmiaru. Wykaż, że niezależnie od zapisanych w nich wartości, interpretowanych jako liczby ze znakiem, instrukcja $\verb@cmp %reg1, %reg2@$ ustawia flagi tak, że $\verb@setl %reg3@$ zadziała zgodnie z oczekiwaniami. Podobnie, wykaż, że jeśli te wartości intepretujemy jako liczby bez znaku, to $\verb@setb %reg3@$ zadziała zgodnie z oczekiwaniami. Wywnioskuj stąd, że pozostałe instrukcje rodziny $\verb@set@$ działają stosownie do swoich sufiksów.      

### Rozwiązanie

### cmp y, x => x - y. Ustawia flagi. Nie zapisuje niczego do destination.

Popatrzmy na te, które będą nas interesować:
|||
|---:|---|
|CF (carry flag - bez znaku) = 1| wtw kiedy wystąpi borrow lub carry
|ZF (zero flag) = 1 | wtw x-y = 0 (x == y)
|SF (sign flag - ze znakiem) = 1 | wtw x-y < 0
|OF (overflow flag - ze znakiem) = 1 | wtw gdy wystąpił overflow/underflow

<br/>

### setl = 1 wtw x < y (SF ^ OF)

Rozpatrzmy wszystkie możliwe przypadki:
```
 y > 0; x > 0; x > y                       OF = 0; SF = 0
 y < 0; x < 0; x < y                       OF = 0; SF = 1
 y < 0; x > 0; x - y > INT64_MAX           OF = 1; SF = 1
 y < 0; x > 0; x - y < INT64_MAX           OF = 0; SF = 0
 y > 0; x < 0; x - y < INT64_MIN           OF = 1; SF = 0
 y > 0; x < 0; x - y > INT64_MIN           OF = 0; SF = 1
```
### setb = 1 wtw x < y (czyli kiedy nastąpiło borrow w trakcie cmp, patrzymy na CF)
```
 x > y             CF = 0;
 x < y             CF = 1;
```

Każda instrukcja z rodziny set działa stosownie do swoich sufiksów, ponieważ "sprawdza" kody warunkowe w taki sposób, aby pokryć wszystkie możliwe przypadki.


### Zadanie 2

Poniżej znajduje się kod funkcji o sygnaturze ``void who(int16_t v[], size_t n)``.
Przetłumacz go na język C i odpowiedz, jaki jest efekt jego wykonania. Czy znajomość sygnatury jest istotna?
```
program odwraca tablice

who:    subq    $1, %rsi                //n=n-1
        movl    $0, %eax                //i=0
.L2:    cmpq    %rsi, %rax              //ustawia flage cf jesli n>i 
        jnb     .L4                    //jeśli flaga cf=0 skacze do L4 program konczy dzialanie           
        leaq    (%rdi,%rax,2), %rcx    //%rcx = v[i]
        movzwl  (%rcx), %r8d           //rejestr %r8d=v[i]
        leaq    (%rdi,%rsi,2), %rdx       //%rdx =v[n] 
        movzwl  (%rdx), %r9d             //rejestr %r9d=v[n]
        movw    %r9w, (%rcx)            //v[i] =rejestr %r9w
        movw    %r8w, (%rdx)            //v[n]= rejest %r8w
        addq    $1, %rax                //i++
        subq    $1, %rsi                //n--
        jmp     .L2                    //bezwarunkowy skok do L2
.L4:    ret
```
```

void who(int16_t v[], size_t n){
    n = n - 1;
    int i = 0;
    while (n > i){
        int64_t a = v[i];
        int64_t b = v[n];
        v[i] = b;
        v[n] = a;
        i = i + 1;
        n = n - 1;
    }
}
```


### Zadanie 3

Poniżej znajduje się kod funkcji o sygnaturze ``bool zonk(char* a, char* b)``, jako argumenty przyjmującej C-owe łańcuchy znaków. Przetłumacz ją na język C (bez instrukcji $\verb@goto@$). Jaką wartość liczy ta funkcja? 

```
zonk:   movl    $0, %ecx           //i = 0
.L2:    movslq  %ecx, %rax          //podstawia %ecx do %rax
        movzbl  (%rdi,%rax), %edx    //%edx = a[i]
        testb   %dl, %dl              //bedzie odpowiadalo za test w forze 
        je      .L6                //wykona skok do .L6  jesli dostaliśmy zf            
        cmpb    %dl, (%rsi,%rax)     // jeśli a[i] != b[i] flaga ~zf
        jne     .L5               //wykona skok do L5 jeśli flaga ~zf
        addl    $1, %ecx          //inkrementuje i
        jmp     .L2               //bezwarunkowy skok do L2
.L6:    orb     (%rsi,%rax), %dl  //or
        sete    %al 
        ret                       //zwraca %rax jako wynik
.L5:    movl    $0, %eax
        ret
```

```
bool zonk(char* a, char* b) {
   int i;
    for(i=0; a[i]; i++) {
        if(b[i] != a[i]) {
            return 0;
        }
    }
    return !(b[i] | a[i]);
}
```

powyższa funkcja zwróci true, ~~jeżeli a zawrze się w b jk~~ gdy ciągi a i b są równe.

### Zadanie 4

Zastąp instrukcje $\verb@pushq %reg1@$ oraz $\verb@popq %reg2@$ równoważnymi ciągami instrukcji jawnie operującymi na stosie.

```
# pushq %reg1   
leaq -8(%rsp), %rsp
movq %reg1, (%rsp)

# popq %reg2
movq (%rsp), %reg2
leaq 8(%rsp), %rsp
```

### Zadanie 5

  Poniżej znajduje się kod funkcji o sygnaturze ``foo(int16_t
    v[], size_t n)``. Przetłumacz ją na język C.  Narysuj ramkę stosu tej funkcji i wytłumacz, jaka jest rola poszczególnych komórek ramki oraz jak jej zawartość zmienia się w trakcie działania. Jaki jest efekt ma ten kod? Jaka jest rola rejestru $\verb@%rbp@$ w tym kodzie?

```
foo:    pushq   %rbp            // rbp wrzucamy na stos
        movq    %rsp, %rbp      // rsp - wskazuje na początek ramki stosu 
        movq    %rdi, -24(%rbp) // adres -24(%rbp) -> początek tablicy v
        movq    %rsi, -32(%rbp) // adres -32(%rbp) -> n
        movq    $0, -8(%rbp)    // adres -8(%rbp) -> wskaźnik i (początkowo ma wartość 0)
        jmp     .L2    // przeskocz do .L2
.L3:    movq    -8(%rbp), %rax        // rax = i
        leaq    (%rax,%rax), %rdx     // rdx = 2*i
        movq    -24(%rbp), %rax       // rax -> początek v
        addq    %rdx, %rax            // rax = v[i] - wskazuje na i-ty element v
        movzwl  (%rax), %eax        // eax = v[i]
        leal    (%rax,%rax), %edx    // edx = 2*v[i]
        movq    -8(%rbp), %rax        // rax = i
        leaq    (%rax,%rax), %rcx    // rcx = 2*i
        movq    -24(%rbp), %rax    // rax - początek v
        addq    %rcx, %rax        // rax przesunięty na i-ty element v
        movw    %dx, (%rax)        // pod adres elementu i-tego wpisujemy dx, czyli 2*v[i]
        addq    $1, -8(%rbp) //  i++
.L2:    movq    -8(%rbp), %rax    // rax = i
        cmpq    -32(%rbp), %rax    // jeśli i < n ustawiana jest flaga CF
        jb      .L3 // jeśli CF to skocz do .L3
        nop
        popq    %rbp // czyścimy stos
        ret
```
Ramka stosu:
%rbp
| i |
|---|
|   |
|v[]|
| n |


W języku C:
```
void foo(int16_t v[0], size_t n){
    for (int i = 0; i < n; i++){
        v[i] = 2*v[i];
    }
}
```
Funkcja foo podwaja wartość n pierwszych elementów tablicy v.

### Zadanie 6

Poniżej znajduje się kod funkcji rekurencyjnej o nieznanej sygnaturze. Przetłumacz tę funkcję na język C, odkryj jej sygnaturę i odpowiedz, jaką wartość ona liczy.
```
1     reccur:
2            pushq   %rbp
3            movq    %rsp, %rbp
4            subq    $16, %rsp
5            movl    %edi, -4(%rbp)
6            cmpl    $0, -4(%rbp)
7            jne     .L2
8            movl    $1, %eax
9            jmp     .L3
10    .L2:   movl    -4(%rbp), %eax
11           subl    $1, %eax
12           movl    %eax, %edi
13           call    reccur
14           imull   -4(%rbp), %eax
15    .L3:   leave
16           ret
```
```
2           odkładamy base pointer na stos
3           zapisujemy nasz nowy szczyt stosu w %rbp
4           dekrementujemy szczyt stosu o 16(stos się powiększa)
5           zapisujemy pierwszy argument(i jedyny) w odpowiednim mu miejscu na stosie
6           porównujemy go z 0
7           jeśli równe 0 to:
8           %eax = 1
9,15,16     dealokujemy obecną ramkę stosu i wracamy do poprzedniej funkcji zwracając %eax
10          jeśli różne od 0 to:
            %eax = argument funkcji
11          %eax--
12          %edi = %eax
13          wywołujemy rekurencyjnie funkcję z argumentem %edi(czyli naszym obecnym - 1)
14          mnożymy nasz obecny argument razy zwróconą wartość wywołania rekurencyjnego
```

```
uint32_t silnia(uint32_t n){
    if(n==0) return 1;
    else return n*silnia(n-1);
}
```


### Zadanie 7

Dana jest funkcja o sygnaturze postaci ``int32_t bar(int32_t a1,...,int32_t an)``, gdzie $\verb@n@$ jest nieznane. Jaka jest minimalna wartość $\verb@n@$, jeżeli wiadomo, że funkcja zwraca wartość jednego ze swoich argumentów, a jej  kod wygląda tak 
```
bar:    pushq   %rbp
        movq    %rsp, %rbp
           .....
        movl    16(%rbp), %eax
        popq    %rbp
        ret
```
Napisz szkic kodu asemblerowego wywołującego funkcję $\verb@bar@$ z liczbą parametrów równą takiemu minimalnemu $\verb@n@$. Zadbaj o poprawne przekazanie argumentów do funkcji. Jak zmieni się napisany przez Ciebie kod, gdy $\verb@n@$ będzie większe?


#### Rozwiązanie:

Ramka funkcji bar wygląda tak:

itd. 
ósmy argument...
siódmy argument (%rsp + 16)
adres powrotu (%rsp + 8)
%rbp          <--- na ten adres wskazuje %rsp
(zobacz ostani slajd z machine-level programming III : Procedures.)

Wiemy gdzie wpisują się kolejne argumenty danej funkcji


|Numer argumentu       | Miejsce zapisu | W rbp po wywolaniu bar |
| -------------------- | - | - |
| arg1  |  rdi | rbp-4 |
| arg2  | rsi | rbp-8 |
| arg3  | rdx | rbp-12 |
| arg4  | rcx | rbp-16 |
| arg5  | r8d | rbp-20 |
| arg6  | r9d | rbp-24 |
| arg7  | rbp+16 | rbp+16 |

Od 7 argumentu kolejne są zapisywane na stosie rbp. Począwszy od 7 zapisanego w $\verb@ rbp+16 @$.
Widzimy, że podany w zadaniu kod assembler odnosi się właśnie do tego miejsca w pamięci. Co oznacz, że funkcjii bar musiał zostać podane co najmniej 7 argumentów.

### n>= 7

#### Fragment assemblera wywolujacy funkcje bar
```
    push    %rbp
    mov     %rsp, %rbp
    push    $7
    mov     $6, %r9d
    mov     $5, %r8d
    mov     $4, %ecx
    mov     $3, %edx
    mov     $2, %esi
    mov     $1, %edi
    call    bar
```
#### Jak zmieni sie kod gdyby n było większe?

Każdy kolejny, dodatkowy argument byłby pushowany na stos.
Na przykład:
```
push    $9
push    $8
push    $7
```
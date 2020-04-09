# Lista ćwiczeniowa nr 3

### Zadanie 1

1. %rax - 0x100 <- to nie dotyczy adresu w pamięci
2. $0x110 -0x110 <- i to też nie. Pozostałe punkty dotyczą.
3. 0x108 - 0xAB 
4. (%rax) - 0xFF 
5. 8(%rax) - 0x100+8=0x108->0xAB 
6. 23(%rax,%rcx) - 0x100+1+23=0x118 ->0x11
7. 0x104(,%rdx,4) - 4*%rdx+0x104=4*3+0x104=0x110->0x13
8. (%rax,%rdx,8) - %rax+8*%rdx=0x100+24=0x118->0x11
9. 265(%rcx,%rdx,2) - %rcx+2*%rdx+256=1+6+265=272=0x110->0x13

### Zadanie 2

 NR PODPUNKTU              | ADRES    | WARTOŚĆ |
| -------------------------| -------- | --------|
|1 addq %rcx,(%rax)        |     0x100     |   0x100      |
|2 subq 16(%rax),%rdx      |     %rdx     | 0xFFFFFFFFFFFFFFF0 | 
|3 shrq $4,%rax            |     %rax     | 0x10 |
|4 incq 16(%rax)           |     0x100     | 0x14 |
|5 decq %rcx               |     %rcx     | 0 |
|6 imulq 8(%rax)           |     %rdx, %rax  | 0xAB00 |
|7 leaq 7(%rcx,%rcx,8),%rdx|     %rdx     | 0x10 |
|8 leaq 0xA(,%rdx,4),%rdx  |     %rdx     | 0x16 |



### Zadanie 3
Dla każdej z poniższych instrukcji wyznacz odpowiedni sufiks (tj. b, w, l lub q) na podstawie rozmiarów operandów:
(b - 1 bajt; w - 2 bajty; l - 4 bajty; q - 8 bajtów)
1. mov**l** %eax,(%rsp)
> Bo  %eax jest rejestrem 32-bitowym.
2. mov**w** (%rax),%dx 
> Bo %dx jest rejestrem 16-bitowym.
3. mov**b** $0xFF, %bl
> Bo %bl jest rejestrem 8-bitowym.
4. mov**b** (%rsp,%rdx,4),%dl
> Bo %dl jest rejestrem 8-bitowym.
5. mov**q** (%rdx),%rax
> Bo %rax jest rejestrem 64-bitowym, a (%rdx) wskazuje na miejsce w pamięci, również 64-bitowe.
6. mov**w** %dx,(%rax)
> Bo %dx jest rejestrem 16-bitowym.


### Zadanie 4

Które z poniższych linii generuje komunikat błędu asemblera i dlaczego?

1. movb $0xF,(%ebx) - **~~W architekurze 64bitowej trzeba używać wskaźników 64 bitowych(8 bajtowych) wiec zamiast (%ebx) (bo on jest 32 bitowy (4 bajtowy), zadziałało by to w architekturze 32bitowej) powinniśmy użyć (%rbx)~~** Jest OK. wartość w %ebx zostanie skonwertowana do 64-bitów.
2. movl %rax,(%rsp) - **Błędny suffix. l tyczy się operandów 32 bitowych (4 bajtowych), a w poleceniu mamy operandy 64 bitowe (8 bajtowe).**
3. movw (%rax),4(%rsp) - **Src i Dest nie mogą jednocześnie odwoływać się do pamięci. Nie możemy bezpośrednio przenosić coś z jednego miejsca pamięci w drugie. Dwa razy () jest nie dozwolone**
4. movb %al,%sl - **Nie ma takiego rejestru jak %sl.**
5. movq %rax,$0x123 - **Dest (drugi operand) jest stałą, a nie możemy przenieść czegoś do stałej.**
6. movl %eax,%rdx - **Błędny suffix. l tyczy się operandów 32 bitowych (4 bajtowych) a %rdx jest operandem 64 bitowym (8 bajtowym)**
7. movb %si,8(%rbp) - **Błędny suffix. b tyczy się operandów 8 bitowych (1 bajtowych) a %si jest operandem 16 bitowym (2 bajtowym)**

### Zadanie 5

Rejestry %rax i %rcx przechowują odpowiednio wartości x i y. Podaj wyrażenie, które będzie opisywać zawartość rejestru %rdx po wykonaniu każdej z poniższych instrukcji:

> leaq bierze source i go wylicza oraz następnie zapisuje do destination. 
1. leaq 6(%rax), %rdx
x+6
2. leaq (%rax, %rcx), %rdx
x+y
3. leaq (%rax, %rcx, 4), %rdx
4*y+x

4. leaq 7(%rax, %rax, 8), %rdx
8*x+x+7=9*x+7

5. leaq 0xA(, %rcx, 4), %rdx
4*y+0+10=4*y+10

6. leaq 9(%rax, %rcx, 2), %rdx
2*y+x+9


### Zadanie 6

Zastąp instrukcję subq %rsi, %rdi równoważnym ciągiem instrukcji bez jawnego użycia operacji odejmowania. Można używać dowolnych innych instrukcji i rejestrów.

Skorzystamy z tego, że:
```
    -x = ~x + 1
```
Więc nasze rozwiązanie wygląda następująco:
```
    notq %rsi
    addq %rsi, %rdi
    incq %rdi
```
Mniej inteligentne (a bardziej oczywiste) rozwiązanie byłoby takie:
```
    notq %rsi
    incq %rsi
    addq %rsi, %rdi
```
Jest tak, ponieważ po negacji %rsi i inkrementacji moglibyśmy osiągnąć overflow i ostateczne dodawanie dało by nam zły wynik. np . dla %rsi = INT_MIN.

### Zadanie 7

Kompilator przetłumaczył funkcję o sygnaturze «uint64_t compute(int64_t x, int64_ty)» na następujący kod asemblerowy.  

```
compute:
    leaq (%rdi,%rsi), %rax
    movq %rax, %rdx
    sarq $31, %rdx
    xorq %rdx, %rax
    subq %rdx, %rax
    ret
```
Argumenty x i y zostały przekazane funkcji compute odpowiednio przez rejestry %rdi i %rsi, a wynik został zwrócony przez instrukcję ret w rejestrze %rax. Jaką
wartość oblicza ta funkcja?

:::info
### Pseudokod
x = %rdi; y = %rsi; sum = %rax; mask = %rdx
sum = x + y // 1
mask = sum >> 31 // 2, 3 
sum = sum ^ mask // 4
sum = sum - mask // 5
return sum
### Tłumaczenie
Na razie załóżmy, że mówimy o liczbach 32 bitowych. Program tworzy nam maskę znaku sumy(same 0 albo 1), w skrócie wygląda to tak:

int mask = sum >> 31;
return (mask ^ sum) - mask;

Prześledźmy 2 przypadki
- dla nieujemnych:
maska to same zera, xor nic nie zmienia, zwracamy nasz x.
- dla ujemnych:
korzystamy z własności dla liczb w U2:\
```- y = ~ y + 1 ```\
nasza maska to same jedynki, xorowanie z jedynkami działa jak negacja, następnie odejmujemy maskę, która ma ujemną wartość.

Jak widzimy funkcja liczy nam abs(x + y) jeśli byłaby 32 bitowa.

###
Teraz popatrzmy na to co się dzieje kiedy funkcja obsługuje 64 bity tak jak w naszym poleceniu. Żeby działała jako abs(x+y) na pewno musi spełniać warunek, że bity sumy(poza bitem znaku) mieszczą się na 31 najmniej znaczących pozycjach. Wtedy abs działa dla dodatnich. Problemem są sumy ujemne, gdyż nie jesteśmy w stanie ich obsłużyć. Nasza maska jest wypełniona jedynkami tylko do połowy(na dodatek w tej połowie, której nie musimy obsługiwać ze względu na nasze założenie o nie przekroczeniu 32 bitów na zaprezentowanie sumy). Zadanie można naprawić używając przesunięcia bitowego o 63.
:::

### Zadanie 8

Rozwiąż poprzednie zadanie dla funkcji int16_t compute2(int8_t m, int8_t s). Jak poprzednio, pierwszy argument został przekazany w rejestrze %rdi, drugi w %rsi a wartość zwracana jest w %rax. Funkcja operuje na 8-, 16-, 32 i 64-bitowych rejestrach, a zwraca wynik w rejestrze 64-bitowym. Wyjaśnij, jak poszczególne wiersze kodu zmieniają starsze bajty rejestrów, których młodszymi bajtami są ich operandy.

```
compute2: 
    movsbw %dil, %di //ta komenda przenosi 
                    //z rejestru b(8 bitowego) do w(16 bitowego)
    movl %edi, %edx // edx = edi, bity starsze 
                    //niż 31 zostaną wyzerowane
    sall $4, %edx //edx zostaje przesunięty o 4 
                    //bity, więc teraz edx = edi*16
    subl %edi, %edx // edx = edx-edi = 15*edi
    leal 0(,%rdx,4), %eax // eax = rdx*4, czyli eax = 4*15*edi 
    movsbw %sil, %si //sil jest rzutowane na 16 bitów 
    addl %esi, %eax // eax = eax + esi = 60*edi + esi
    ret // zwraca nam wartość rejestru
        //eax, czyli 60*edi + esi = 60*m + s
```


### Zadanie 9

Zinterpretuj poniższe stałe szesnastkowe jako liczby pojedyńczej precyzji (32- bitowe) w formacie IEEE 754, następnie wykonaj dodawania i zapisz wynik w takim samym formacie.

1. 0xC0D20004 + 0x72407020
2. 0xC0D20004 + 0x40DC0004
3. (0x5FBE4000 + 0x3FF80000) + 0xDFDE4000

Punkt 1.

0xC0D20004 = bx11000000110100100000000000000100

Bit zanku = 1
Wykładnik = bx10000001 - bias = 129 - 127 = 2
Mantysa = bx1.10100100000000000000100

0x72407020 = bx01110010010000000111000000100000
Wykładnik = bx11100100 - bias = 228 - 127 = 101
Mantysa = bx1.10000000111000000100000

Aby dodać te dwie wartości musimy tę o mniejszym wykładniku sprowadzić do wykładnika większego ze składników sumy. Przesuwamy wtedy odpowiednio mantysę. 

W tym przpadku różnica wykładników jest na tyle duża, że mantysa składnika o mniejszym wykłądniku zostanie wyzerowana. W takim razie rezultatem tej sumy jest po prostu drugi z jej składników.

Wynik:
0x72407020 = bx01110010010000000111000000100000
Wykładnik = bx11100100 - bias = 228 - 127 = 101
Mantysa = bx1.10000000111000000100000



Punkt 2.
0xCOD20004 = 1 10000001 10100100000000000000100 // Zapisanie liczby binarnie
            -1 * 2^2 * 10100100000000000000100 // Zapisanie znaku, potęgi w   systemie dziesiętnym oraz mantysy binarnie 
exp= 10000001(2) - 127 = 129 - 127 = 2

0x40DC0004 = 0 10000001 10111000000000000000100 
             1 * 2^2 * 10111000000000000000100
             
             
             1.10111000000000000000100 *2^2
            -1.10100100000000000000100 *2^2
            =0.00010100000000000000000 *2^2 = // Przesunięcie o 4 w lewo
             1.01000000000000000000000 *2^-2 = // Zapisanie w IEEE754 bin
             0 01111101 01000000000000000000000 = //Zapisasnie w IEEE754 hex
             0x0x3ea00000
              
Punkt 3.

0x5FBE4000 = 0	10111111	01111100100000000000000 (binarnie w postaci IEEE754)
exp=191
bias=2^(k-1)^-1=127
e=exp-bias=64

0x5FBE4000= 1.01111100100000000000000 * 2^64^


0x3FF80000= 0	01111111	11110000000000000000000 (binarnie w postaci IEEE754)
exp=127
e=exp-bias=0

0x3FF80000= 1.11110000000000000000000 * 2^0^

0x5FBE4000+0x3FF80000:
```
     1.01111100100000000000000 * 2^64
    +1.11110000000000000000000 * 2^0
    
    Normalizacja wykładnika do 64:
    
     1.01111100100000000000000 * 2^64
    +0.00000000000000000000000... 111110000000000000000000 * 2^64 (zostanie wyzerowana ta liczba, bo pierwsze 63 bity tej liczby to zera w postaci dla tego wykładnika, a mantysa z jedynką wiodąco miesci tylko 24 pierwsze bity)
    =1.01111100100000000000000 * 2^64 = 0x5FBE4000
    
    
```
(0x5FBE4000+0x3FF80000)+0xDFDE4000:
0xDFDE4000=1	10111111	10111100100000000000000 (binarnie w postaci IEEE754)
exp=191
e=exp-bias=64

0xDFDE4000= -1.10111100100000000000000 * 2^64

(0x5FBE4000+0x3FF80000)+0xDFDE4000:
```
     1.01111100100000000000000 * 2^64
    -1.10111100100000000000000 * 2^64
    =0.01000000000000000000000 * 2^64
    -0.10000000000000000000000 * 2^64
   =-0.01000000000000000000000 * 2^64 = (normalizacja mantysy - jedynka na najbadziej znaczącym bicie)
   =-1.00000000000000000000000 * 2^62 
   
   e=exp-bias
   2=exp-127
   exp=127+2=129
   exp: 10000001
   
   (0x5FBE4000+0x3FF80000)+0xDFDE4000= (IEE754):
   1 10000001 00000000000000000000000
  =0xC08000000
    
```
> [name=Piotr Witkowski] A mi wyszedł wzorzec: 0xDE800000. Jeśli jest błąd to jest on w ostatnim dodawaniu. (być może, a nawet prawdopodobnie, że mam błędny wynik). Można to zweryfikować programem w C:
> 
```
#include<assert.h>
#include<stdio.h>
#include<stdint.h>


typedef union {
  int32_t i;
  float f;
} if_u; 


int main(void) {

printf("Rozmiar unii w bajtach: %d\n", sizeof(if_u));

 if_u a, b, c;
 a.i = 0xC0D20004;
 b.i = 0x40DC0004;

 printf("a = %f\n", a.f); 
 printf("b = %f\n", b.f); 

 c.f = a.f + b.f;
 printf("c = %f\n", c.f); 
 /*Ale uwaga, powyższy printf może nie wypisać wszystkich cyfr 
 znaczących. Dlatego lepiej wypisać wartość całkowitą c.i 
i porównać z wzorcem bitowym wyliczonym ręcznie!*/

 return 0;
}

```
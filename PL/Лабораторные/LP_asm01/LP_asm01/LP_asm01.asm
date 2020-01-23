.586P
.MODEL FLAT, STDCALL

ExitProcess PROTO : DWORD
getmin PROTO: DWORD, : DWORD

.STACK 4096

.CONST

.DATA
ARR     DWORD 11, 44, 10, 39, 5, 22, 12, 100, 50, 33
NUM     DWORD 10
MIN     DWORD ?

.CODE

getmin PROC array : DWORD, numer : DWORD
   mov ebx, array
   mov eax, [ebx]
   mov MIN, eax
   mov ecx, numer
   CYCLE:
   mov edx, [ebx]
   cmp edx, MIN
   ja fa
   jb fb
fa:
   add ebx, 4
   LOOP  CYCLE
   jmp fin
fb:
   mov eax, [ebx]
   mov MIN, eax
   add ebx, 4
   LOOP  CYCLE
   jmp fin

fin:                ;«¿œ»—¿“‹ ¬ –≈√»—“– –≈«”À‹“¿“, ¬ Àﬁ¡Œ…
   ret
getmin ENDP


main PROC
START :
   push NUM
   push offset ARR
   call getmin
   push MIN
   call ExitProcess
main ENDP

end main
.586P
.MODEL FLAT, STDCALL

ExitProcess PROTO : DWORD
includelib kernel32.lib
getmin PROTO: DWORD, : DWORD
getmax PROTO: DWORD, : DWORD

SetConsoleTitleA PROTO :DWORD
GetStdHandle PROTO :DWORD
WriteConsoleA PROTO :DWORD,:DWORD,:DWORD,:DWORD,:DWORD


.STACK 4096

.CONST

consoletitle db 'int_to_char', 0
stroka db 'getmax - getmin = ', 0

.DATA
ARR     DWORD 11, 44, 10, 39, 5, 22, 12, 100, 50, 33
NUM     DWORD 10
S       DWORD ?
RESULT byte 40 dup(0)

consolehandle dd 0h

.CODE

printconsole PROC uses eax ebx ecx edi esi, pstr: DWORD, ptitle: DWORD
 
   push ptitle
   call SetConsoleTitleA

   push -11
   call GetStdHandle

   mov esi, pstr
   mov edi, -1
count:
   inc edi
   cmp byte ptr [esi + edi], 0
   jne count

   push 0
   push 0
   push edi
   push pstr
   push eax
   call WriteConsoleA

   ret
   printconsole ENDP

int_to_char PROC uses eax ebx ecx edi esi, pstr: dword, intfield: dword

   mov edi, pstr
   mov esi, 0
   mov eax, intfield
   cdq ; знак распространители с eax на edx
   mov ebx, 10
   idiv ebx ; eax=eax/ebx
   test eax,80000000h ; резалт отрицательный?
   jz plus
   neg eax
   neg edx
   mov cl, '-'
   mov [edi], cl
   inc edi ; ++edi

plus: 
   push dx
   inc esi
   test eax, eax
   jz fin
   cdq 
   idiv ebx
   jmp plus

fin: 
   mov ecx, esi
write:
   pop bx
   add bl, '0'
   mov [edi], bl
   inc edi
   loop write

ret

int_to_char ENDP


main PROC
START :

   
   push NUM
   push offset ARR
   call getmax
   mov S, eax
   push NUM
   push offset ARR
   call getmin
   sub S, eax
  
   push S
   push offset RESULT
   call int_to_char

   push offset consoletitle
   push offset stroka
   call printconsole

   push offset consoletitle
   push offset RESULT
   call printconsole

   push 228
   call ExitProcess
main ENDP

end main
.586P
.MODEL FLAT, stdcall

.CODE

asm24l PROC parm:dword
 mov eax, parm
 neg eax
 ret
 asm24l ENDP

getmin PROC array : DWORD, numer : DWORD
mov ebx, array
mov eax, [ebx]
mov ecx, numer
CYCLE:
mov edx, [ebx]
cmp edx, eax
ja fa
jb fb

fa:
add ebx, 4
LOOP CYCLE
jmp fin

fb:
mov eax, [ebx]
add ebx, 4
LOOP CYCLE
jmp fin

fin:
ret
getmin ENDP


getmax PROC array : DWORD, numer : DWORD
mov ebx, array
mov eax, [ebx]
mov ecx, numer
CYCLE:
mov edx, [ebx]
cmp edx, eax
ja fa
jb fb

fa:
mov eax, [ebx]
add ebx, 4
LOOP CYCLE
jmp fin

fb:
add ebx, 4
LOOP CYCLE
jmp fin

fin:
ret
getmax ENDP

end
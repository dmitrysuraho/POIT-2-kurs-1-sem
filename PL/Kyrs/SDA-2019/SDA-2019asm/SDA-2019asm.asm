.586
.MODEL FLAT, stdcall
includelib libucrt.lib
includelib kernel32.lib
ExitProcess PROTO : DWORD

Unicode PROTO: DWORD
RandNum PROTO
WriteInConsoleChar PROTO: DWORD
WriteInConsoleUnint PROTO: DWORD

PF PROTO: DWORD
SF PROTO: DWORD

.STACK 8192

.CONST

	L0 DWORD 2
	L1 DWORD 1
	L2 DWORD 3
	L3 DWORD 5
	L4 DWORD 10
	L5 DWORD 4
	L6 DWORD "f", 0
	L7 DWORD 0eh
	L8 DWORD 0

.DATA

	ret_PF DWORD ?
	ret_SF DWORD ?
	PFY DWORD ?
	PFL DWORD ?
	SFN DWORD ?
	mainA DWORD ?
	mainB DWORD ?
	mainC DWORD ?
	mainD DWORD ?
	mainE DWORD ?
	mainF DWORD ?

.CODE

PF PROC X: DWORD
	call RandNum
	push eax
	pop PFL
	push PFL
	call WriteInConsoleUnint
	push PFL
	push X
	pop eax
	pop ebx
	add eax, ebx
	push eax
	push L0
	pop eax
	pop ebx
	mul ebx
	push eax
	pop PFY
	push PFY
	push L1
	pop ebx
	pop eax
	shl eax, 1
	push eax
	pop PFY
	push PFY
	pop ret_PF
ret
PF ENDP

SF PROC M: DWORD
	push L0
	push M
	call Unicode
	push eax
	push L2
	pop eax
	pop ebx
	mul ebx
	push eax
	pop eax
	pop ebx
	add eax, ebx
	push eax
	pop SFN
	push SFN
	push L1
	pop ebx
	pop eax
	shr eax, 1
	push eax
	pop SFN
	push SFN
	pop ret_SF
ret
SF ENDP

main PROC
START:
	push L3
	pop mainA
	mov ecx, 3
CYRCLE110:
push ecx
	push mainA
	push L4
	pop eax
	pop ebx
	add eax, ebx
	push eax
	pop mainA
pop ecx
LOOP CYRCLE110
	push L5
	pop mainB
	push L6
	pop mainC
	push mainB
	call PF
	push ret_PF
	pop mainD
	push mainC
	call SF
	push ret_SF
	pop mainE
	push L7
	pop mainF
	push mainA
	call WriteInConsoleUnint
	push mainD
	call WriteInConsoleUnint
	push mainE
	call WriteInConsoleUnint
	push mainF
	call WriteInConsoleUnint

	push L8
	call ExitProcess
main ENDP

end main
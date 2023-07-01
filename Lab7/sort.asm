TITLE Sort

.DOSSEG
.8086
.NO87
.MODEL TINY

.DATA
buffer DB 256 DUP (?)
str_buf DW buffer
str_len DW ?

.CODE
.STARTUP
    push str_buf
    call read_string
    add sp, 2

    mov bx, str_buf

    mov al, [bx+1]
    mov str_len, ax
    mov cx, 0

loop_sort:
    mov si, -1

    mov di, str_len
    dec di
    sub di, cx
loop_swap:
    inc si
    cmp di, si
    jz next

    mov al, BYTE PTR [bx+2+si]

    cmp al, BYTE PTR [bx+3+si]
    jg swap

next:
    inc cx
    cmp str_len, cx
    jnz loop_sort

    mov al, '$'
    mov si, str_len
    mov BYTE PTR [bx+2+si], al

    ; 화면 출력
    mov ah, 09h
    lea dx, [bx+2]
    int 21h

    ; 프로그램 종료
    mov ah, 4Ch
    xor al, al
    int 21h

swap:
    xchg al, BYTE PTR [bx+3+si]
    xchg al, BYTE PTR [bx+2+si]

    jmp loop_swap

INCLUDE readstr.inc

END
TITLE Sort

.DOSSEG
.8086
.NO87
.MODEL TINY

.DATA
buffer DB 256 DUP (?)
str_buf DW buffer
last_idx DW ?

.CODE
.STARTUP
    push str_buf
    call read_string
    add sp, 2

    mov ax, [str_buf + 1]
    mov dx, 2
    mov cx, 0

    mov last_idx, ax
    add last_idx, 2

loop_bubble:
    mov si, 2
    mov bx, last_idx
    dec bx
    sub bx, cx

loop_swap:
    mov ax, [str_buf][si]
    cmp ax, [str_buf][si + 1]

    jg swap

    inc si
    cmp bx, si
    jne loop_swap

    inc dx
    inc cx
    cmp last_idx, dx
    jne loop_bubble

    mov bx, last_idx
    mov [str_buf][bx], '$'

    mov al, 09h
    lea dx, buffer
    int 21h

    ; 프로그램 종료
    mov ah, 4Ch
    xor al, al
    int 21h

swap:
    xchg ax, [str_buf][si + 1]

    inc si
    cmp bx, si
    jne loop_swap

INCLUDE readstr.inc

END
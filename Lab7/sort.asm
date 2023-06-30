TITLE Sort

.DOSSEG
.8086
.NO87
.MODEL TINY

.DATA
buffer DB 256 DUP (?)
strbuf DW buffer

.CODE
.STARTUP
    push strbuf
    call read_string
    add sp, 2

    mov cx, buffer[2]
    
    ; 프로그램 종료
    mov ah, 4Ch
    xor al, al
    int 21h

INCLUDE readstr.inc

END
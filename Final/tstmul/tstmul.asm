TITLE Final
.DOSSEG
.8086
.NO87
.MODEL TINY

D21_TERMINATE EQU 4Ch

.DATA
num0 DB 5
num1 DB 2
num3 DD 2.12
res DB ?

.CODE
.STARTUP
    mov al, num0
    sub al, num1
    mov bl, al
    mul bl

    mov res, al

    mov ax, OFFSET num3

terminate:
    mov ah, D21_TERMINATE
    xor al, al
    int 21h
END
TITLE Final
.DOSSEG
.8086
.NO87
.MODEL TINY

D21_TERMINATE EQU 4Ch
ARRAY_SIZE EQU 7

.DATA
src DW 73, 23, 17, 88, 52, 89, 52
dst DW ARRAY_SIZE DUP (?)

.CODE
.STARTUP
    ; src를 dst로 복사
    mov cx, ARRAY_SIZE
    mov si, OFFSET src
    mov di, OFFSET dst

    rep movsw

terminate:
    mov ah, D21_TERMINATE
    xor al, al
    int 21h
END
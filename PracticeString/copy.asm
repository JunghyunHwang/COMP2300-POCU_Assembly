TITLE Copy String

.DOSSEG
.8086
.NO87
.MODEL TINY

BUFSIZE EQU 255

.DATA
src DB BUFSIZE
    DB BUFSIZE+1 DUP (?)
dst DB BUFSIZE DUP (?)

.CODE
.STARTUP
printstr MACRO str
    lea dx, dst
    mov ah, 09h
    int 21h
ENDM
    lea dx, src
    mov ah, 0Ah
    int 21h

    mov bx, OFFSET src

    mov al, '$'
    mov si, [bx+1]
    mov BYTE PTR [bx+2+si], al

    std
    mov cx, [bx+1]
    mov si, [bx+2]
    mov di, OFFSET dst
    rep movsb

    printstr dst

    ; End program
    mov ah, 4Ch
    xor al, al
    int 21h
END

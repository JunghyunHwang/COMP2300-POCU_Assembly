TITLE Formatted Print

.DOSSEG
.8086
.NO87
.MODEL TINY

BUFSIZE EQU 255

.DATA
newline DB 0Ah,0Dh,'$'
input_msg DB "Enter your string$"

str_in DB BUFSIZE
       DB BUFSIZE+1 DUP (?)


.CODE
.STARTUP
printstr MACRO str ;(str) <ah,dx>
    lea dx, str
    mov ah, 9h
    int 21h
ENDM

printchar MACRO char ;(char) <>
    mov dl, char
    mov ah, 02h
    int 21h
ENDM

    ; Write messaeg
    printstr input_msg
    printstr newline

    ; Direct console input number
    mov ah, 07h
    int 21h

    printchar al

    ; End program
    mov ah, 4Ch
    xor al, al
    int 21h

END

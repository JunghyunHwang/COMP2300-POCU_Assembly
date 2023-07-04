BUFSIZE EQU 255

.DATA
newline DB 0Ah,0Dh,'$'
input_msg DB "Enter a file name$"

buffer_in DB BUFSIZE
          DB BUFSIZE+1 DUP (?)

.CODE
.STARTUP
printstr MACRO str ;(str) <ah,dx>
    lea dx, str
    mov ah, 9h
    int 21h
ENDM

    printstr input_msg
    printstr newline

    ; input file name
    mov ah, 0Ah
    lea dx, buffer_in
    int 21h

    printstr newline

    ; Add end string character
    mov bh, 0h
    mov bl, buffer_in[1]
    mov buffer_in[bx+2],'$'

    mov ah, 09h
    lea dx, buffer_in[2]
    int 21h

    mov ah, 4Ch
    xor al, al
    int 21h
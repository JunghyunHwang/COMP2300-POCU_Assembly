BUFSIZE EQU 255
FILENAME EQU 20

.DATA
newline DB 0Ah,0Dh,'$'
input_msg DB "Enter a file name$"
typing_msg DB "Start typing$"

file_name DB FILENAME
          DB FILENAME+1 DUP (?)
buf_sen DB BUFSIZE DUP (?)
sen_len DW ?

.CODE
.STARTUP
printstr MACRO str ;(str) <ah,dx>
    lea dx, str
    mov ah, 9h
    int 21h
ENDM

printchar MACRO char
    mov dl, char
    mov ah, 02h
    int 21h
ENDM

readchar MACRO
    mov ah, 07h
    int 21h
ENDM

    printstr input_msg
    printstr newline

    ; input file name
    lea dx, file_name
    mov ah, 0Ah
    int 21h

    lea bx, file_name
    mov si, [bx+1]
    mov BYTE PTR [bx+si], '$'

    ; File open
    mov ah, 3Dh
    mov al, 0
    lea dx, file_name[2]
    int 21h

    ; File read
    mov bx, ax
    mov cx, BUFSIZE
    lea dx, buf_sen
    mov ah, 3Fh
    int 21h

    lea bx, buf_sen
    mov sen_len, ax
    mov si, sen_len
    mov BYTE PTR [bx+si], '$'

    printstr typing_msg
    printstr newline

    printstr buf_sen
    printstr newline

    mov cx, sen_len
    mov si, -1
loop_type:
    inc si
    readchar
    cmp al, 0Dh
    jz exit
    
    printchar al

    loop loop_type

exit:
    mov ah, 4Ch
    xor al, al
    int 21h
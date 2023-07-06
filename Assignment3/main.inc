BUFSIZE EQU 255
FILENAME EQU 13

.DATA
newline DB 0Ah,0Dh,'$'
input_msg DB "Enter a file name", 0Ah, 0Dh, '$'
typing_msg DB "Start typing", 0Ah, 0Dh, '$'
err_msg DB "Typo occurred", 0Ah, 0Dh, '$'

file_name DB FILENAME
          DB FILENAME+1 DUP (?)
buf_sen DB BUFSIZE DUP (?)
sen_len DW ?

vector DD ?
ptr_handler DW int3_handler

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
    mov ax, 3504h
    int 21h

    mov vector[0], bx
    mov vector[2], es

    printstr input_msg

    ; input file name
    lea dx, file_name
    mov ah, 0Ah
    int 21h

    lea bx, file_name
    mov al, 0h
    mov dl, BYTE PTR [bx+1]
    mov si, dx
    mov BYTE PTR [bx+2+si], al

    ; File open
    mov ah, 3Dh
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

    printstr buf_sen
    printstr newline

    mov bx, OFFSET buf_sen
    mov cx, sen_len
    mov si, -1
loop_type:
    inc si

    readchar
    mov ah, 0h
    cmp al, 0Dh
    jz exit

    ; Check typo
    mov dh, 0h
    mov dl, BYTE PTR [bx+si]
    assert dx, ax, err_msg

    printchar al

    loop loop_type

restore:
    lea dx, vector
    mov ax, 2503h
    int 21h

exit:
    mov ah, 4Ch
    xor al, al
    int 21h

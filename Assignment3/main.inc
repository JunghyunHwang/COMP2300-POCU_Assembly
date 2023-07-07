BUFSIZE EQU 255
FILENAME EQU 13

.DATA
newline DB 0Dh,0Ah,'$'
input_msg DB "Enter a file name",0Dh,0Ah,'$'
typing_msg DB "Start typing",0Dh,0Ah,'$'
err_msg DB "Typo!",0Dh,0Ah,'$'

file_name DB FILENAME
          DB FILENAME+1 DUP (?)
buf_sen DB BUFSIZE+1 DUP (?)

sen_len DW ?
vector DD ?

.CODE
.STARTUP
printstr MACRO str ;(str) <ah,dx>
    lea dx, str
    mov ah, 09h
    int 21h
ENDM

printchar MACRO char
    push ax
    push dx

    mov dl, char
    mov ah, 02h
    int 21h

    pop dx
    pop ax
ENDM

readchar MACRO
    mov ah, 07h
    int 21h
ENDM

    ; Get interrupt
    mov ax, 3503h
    int 21h

    lea si, vector
    mov [si], bx
    mov [si+2], es

    ; Set interrupt
    push ds
    mov ax, cs
    mov ds, ax
    mov dx, OFFSET int3_handler
    mov ax, 2503h
    int 21h
    pop ds

    printstr input_msg

    ; input file name
    lea dx, file_name
    mov ah, 0Ah
    int 21h

    lea bx, file_name
    mov dl, BYTE PTR [bx+1]
    mov si, dx
    mov al, 0h
    mov BYTE PTR [bx+2+si], al

    ; File open
    mov al, 0h
    mov ah, 3Dh
    lea dx, file_name[2]
    int 21h

    ; File read
    mov bx, ax
    mov cx, BUFSIZE
    lea dx, buf_sen
    mov ah, 3Fh
    int 21h

    cmp ax, 0
    jz exit
    
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
    mov ah, 00h
    cmp al, 0Dh
    jz exit

    printchar al
    mov dh, 00h
    mov dl, BYTE PTR [bx+si]
    assert dx, ax, err_msg

    loop loop_type

exit:
    lds dx, vector
    mov ax, 2503h
    int 21h

    mov ah, 4Ch
    xor al, al
    int 21h
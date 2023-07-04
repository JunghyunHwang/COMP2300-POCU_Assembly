TITLE Formatted Print

.DOSSEG
.8086
.NO87
.MODEL TINY

BUFSIZE EQU 255

.DATA
newline DB 0Ah,0Dh,'$'
input_msg DB "Enter your string$"

src DB BUFSIZE
    DB BUFSIZE+1 DUP (?)
dst DB BUFSIZE DUP (?)

abs_num DB ?
min_num DB ?
max_num DB ?
str_len DB ?

.CODE
.STARTUP
printstr MACRO str ;(str) <ah,dx>
    lea dx, str
    mov ah, 9h
    int 21h
ENDM

printchar MACRO char ;(char) <ah, dl>
    mov dl, char
    mov ah, 02h
    int 21h
ENDM

    ; Write messaeg
    printstr input_msg
    printstr newline

    lea dx, src
    mov ah, 0Ah
    int 21h

    printstr newline

    mov bx, OFFSET src
    mov cl, [bx+1]
    mov str_len, cl

    ; Direct console input number
    mov ah, 07h
    int 21h

    printchar al

    mov cl, al

    ; Direct console input number
    mov ah, 07h
    int 21h

    printchar al

    mov ah, 0
    mov ch, 0

    cmp ax, cx
    jb swap

store_num:
    mov max_num, al
    mov min_num, cl
    mov abs_num, al
    sub abs_num, cl
    add abs_num, 30h
    
    printstr newline
    mov ah, 0

    mov bx, OFFSET src

    mov si, 0
    mov di, 0

str_copy:
    mov al, BYTE PTR [bx+2+si]
    cmp al, '%'
    jz chk_form

copy_dst:
    mov BYTE PTR dst[di], al

    inc si
    inc di
    mov al, str_len

    cmp ax, si
    jg str_copy

display:
    mov al, '$'
    mov BYTE PTR dst[di], al

    ; diplay
    printstr dst

    ; End program
    mov ah, 4Ch
    xor al, al
    int 21h

swap:
    xchg ax, cx

    jmp store_num

chk_form:
    mov dl, BYTE PTR [bx+2+si+1]
    cmp dl, 'm'
    jz set_min

    cmp dl, 'M'
    jz set_max

    cmp dl, 'd'
    jz set_abs

    jmp copy_dst

set_min:
    inc si
    mov al, min_num

    jmp copy_dst

set_max:
    inc si
    mov al, max_num

    jmp copy_dst

set_abs:
    inc si
    mov al, abs_num

    jmp copy_dst
END

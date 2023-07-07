TITLE Interrupt

.DOSSEG
.8086
.NO87
.MODEL TINY

.DATA
    msg DB "Hi bro!$"
    newline DB 0Ah,0Dh,'$'
.CODE
.STARTUP

    mov cx, 05h
print_loop:
    dec cx
    jl exit

    lea dx, msg
    mov ah, 09h
    int 21h

    cmp cx, 0
    jnz print_line
    jz call_int
    jmp print_loop

exit:
    mov ax, 4C00h
    int 21h

print_line:
    lea dx, newline
    mov ah, 09h
    int 21h

    jmp print_loop

call_int:
    int 03h
END
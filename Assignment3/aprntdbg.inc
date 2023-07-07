int3_handler PROC FAR
    mov dx, di
    mov ah, 09h
    int 21h

    lds dx, vector
    mov ax, 2503h
    int 21h

    int 03h

    push ds
    mov ax, cs
    mov ds, ax
    mov dx, OFFSET int3_handler
    mov ax, 2503h
    int 21h
    pop ds

    iret
int3_handler ENDP
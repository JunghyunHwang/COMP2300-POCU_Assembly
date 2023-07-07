int3_handler PROC FAR
    mov dx, di
    mov ah, 09h
    int 21h

    lds dx, vector
    call dx

    iret
int3_handler ENDP
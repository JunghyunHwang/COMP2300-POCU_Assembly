int3_handler PROC FAR
    mov dx, di
    mov ah, 09h
    int 21h

    mov di, OFFSET vector
    jmp FAR PTR [di]

    iret
int3_handler ENDP
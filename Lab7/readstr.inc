read_string PROC NEAR
    push bp
    mov bp, sp

    mov bx, [bp+4]
    mov BYTE PTR [bx+1], 0

    pop bp
    ret
read_string ENDP
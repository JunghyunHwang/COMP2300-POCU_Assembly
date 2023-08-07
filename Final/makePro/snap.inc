finger_snap PROC NEAR
    push bp
    mov bp, sp

    mov ax, [bp+4]
    shr ax, 1

    pop bp
    ret
finger_snap ENDP
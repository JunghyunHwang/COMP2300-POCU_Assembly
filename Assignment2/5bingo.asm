MASK_CALLED=%10000000
called_num=$00

callnum:
    .SUBROUTINE
    ldx #LEN-1

loop:
    lda table,x
    cmp called_num
    beq .ret
    
    dex
    bne loop

    lda table,x
    cmp called_num
    beq .ret
    rts

.ret:
    ora #MASK_CALLED
    sta table,x
    rts
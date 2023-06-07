MASK_CALLED=%10000000
called_num=$00

callnum:
    .SUBROUTINE

    lda called_num
    ldx #LEN-1

loop:
    cmp table,x
    beq .set_bit
    
    dex
    bpl loop

    rts

.set_bit:
    ora #MASK_CALLED
    sta table,x

    rts
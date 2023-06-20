sum:
    lda pnum
    pha
    beq exit

    sec
    sbc #1
    sta pnum
    
    jsr sum

exit:
    pla
    clc
    adc pnum
    sta pnum
    sta ret

    rts
rettmp=$10

callnum:
    pla
    sta rettmp
    pla
    sta rettmp+1

    ;address
    pla
    pla

    ;size
    pla

    ;num
    pla

    lda rettmp+1
    pha
    lda rettmp
    pha

    rts

won:
    rts
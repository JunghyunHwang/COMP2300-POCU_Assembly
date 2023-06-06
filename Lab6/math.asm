ret_min=$20
PG1=$0100
regtmp=$00
rettmp=regtmp+3
tmp=regtmp+5
in_maxaddr=$0010

;========================;
;==========min===========;
;========================;
min:
    .SUBROUTINE
    sta regtmp
    stx regtmp+1
    sty regtmp+2

    tsx

    lda PG1+3,x
    cmp PG1+4,x
    bcs .left_min

    sta ret_min
    jmp .restore

.left_min:
    lda PG1+4,x
    sta ret_min

.restore:
    lda regtmp
    ldx regtmp+1
    ldy regtmp+2

    rts

;========================;
;==========max===========;
;========================;
max:
    .SUBROUTINE
    sta regtmp
    sty regtmp+2

    ldx in_maxaddr
    cpx in_maxaddr+1
    bcs .restore

.right_max
    ldx in_maxaddr+1

.restore
    lda regtmp
    ldy regtmp+2

    rts

;========================;
;==========minmax========;
;========================;
minmax:
    .SUBROUTINE
    sta regtmp
    stx regtmp+1
    sty regtmp+2
    
    pla
    sta rettmp+1
    pla
    sta rettmp

    pla
    sta tmp
    pla
    sta tmp+1
    pla
    pla

    lda tmp
    cmp tmp+1
    bcc .a_not_max

    pha
    lda tmp+1
    pha
    jmp .restore

.a_not_max
    tax
    lda tmp+1
    pha

    txa
    pha

.restore
    lda rettmp
    pha
    lda rettmp+1
    pha

    lda regtmp
    ldx regtmp+1
    ldy regtmp+2

    rts
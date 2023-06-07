ret_min=$20
PG1=$0100
regtmp=$00
retaddr=regtmp+3
vtmp=retaddr+2
outaddr=vtmp+2
inaddr=$0010

;========================;
;==========min===========;
;========================;
min:
    .SUBROUTINE
    sta regtmp
    stx regtmp+1

    tsx

    lda PG1+3,x
    cmp PG1+4,x
    bcs .a_not_min

    sta ret_min
    jmp .restore

.a_not_min:
    lda PG1+4,x
    sta ret_min

.restore:
    lda regtmp
    ldx regtmp+1

    rts

;========================;
;==========max===========;
;========================;
max:
    .SUBROUTINE
    sta regtmp

    ldx inaddr
    cpx inaddr+1
    bcs .restore

.right_max
    ldx inaddr+1

.restore
    lda regtmp

    rts

;========================;
;=========minmax=========;
;========================;
minmax:
    .SUBROUTINE
    sta regtmp
    stx regtmp+1

    pla
    sta retaddr
    pla
    sta retaddr+1
    
    tsx

    lda PG1+1,x
    cmp PG1+2,x
    bcc .a_not_max

    sta PG1+4,x

    lda PG1+2,x
    sta PG1+3,x
    jmp .restore

.a_not_max
    sta PG1+3,x
    
    lda PG1+2,x
    sta PG1+4,x

.restore
    inx
    inx
    txs

    lda retaddr+1
    pha

    lda retaddr
    pha

    lda regtmp
    ldx regtmp+1
    
    rts


;========================;
;==========mmref=========;
;========================;
mmref:
    .SUBROUTINE

    sta regtmp
    stx regtmp+1

    pla
    sta retaddr
    pla
    sta retaddr+1

    pla
    sta vtmp

    pla
    sta outaddr
    pla
    sta outaddr+1
    pla
    sta outaddr+2
    pla
    sta outaddr+3

    lda inaddr
    cmp vtmp
    bcc .a_not_max

    ldx #2
    sta (outaddr,x)

    ldx #0
    lda vtmp
    sta (outaddr,x)
    jmp .restore

.a_not_max
    ldx #0
    sta (outaddr,x)

    ldx #2
    lda vtmp
    sta (outaddr,x)

.restore
    lda retaddr+1
    pha
    lda retaddr
    pha

    lda regtmp
    ldx regtmp+1

    rts
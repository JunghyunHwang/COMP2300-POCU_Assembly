MARK_CALLED=%10000000
PG1=$0100
vret=$01
rettmp=$10
tbladdr=rettmp+2
bgsize=tbladdr+3
lastidx=bgsize+2
vtmp=lastidx+1

;=================
;====callednum====
;=================
callnum:
    .SUBROUTINE
    pla
    sta rettmp
    pla
    sta rettmp+1

    pla
    sta tbladdr
    pla
    sta tbladdr+1

    pla
    sta bgsize
    tax

.cal_size:
    dex
    beq .chk_ele

    clc
    adc bgsize
    jmp .cal_size
    

.chk_ele:
    tay
    dey

    pla
    tax

    lda rettmp+1
    pha
    lda rettmp
    pha

    txa
.loop:
    cmp (tbladdr),y
    beq .set_bit

    dey
    bpl .loop

    rts

.set_bit:
    ora #MARK_CALLED
    sta (tbladdr),y
    rts

;=================
;=======won=======
;=================
won:
    .SUBROUTINE
    tsx

    lda PG1+3,x
    sta tbladdr
    lda PG1+4,x
    sta tbladdr+1

    lda PG1+5,x
    tay
    iny

    tax
    dex
    
    stx bgsize-1
    sta bgsize
    sty bgsize+1

    tax
    clc
.cal_idx:
    dex
    beq .dia_bu

    adc bgsize
    jmp .cal_idx

;=====diagonal=====
.dia_bu:
    tay
    dey
    sty lastidx

    lda (tbladdr),y
    bpl .dia_td

    ldx bgsize
.bu_loop:
    dex
    beq .bingo

    tya
    sec
    sbc bgsize+1
    tay

    lda (tbladdr),y
    bmi .bu_loop

.dia_td:
    ldy bgsize-1
    lda (tbladdr),y
    bpl .vertical

    ldx bgsize
.td_loop:
    dex
    beq .bingo

    tya
    clc
    adc bgsize-1
    tay

    lda (tbladdr),y
    bmi .td_loop

    jmp .vertical

.bingo:
    lda #1
    sta vret
    rts

;=====vertical=====
.vertical:
    ldy bgsize-1
    tya
    tax

    lda (tbladdr),y
    bmi .v_loop

.set:
    dex
    bmi .horizontal

    txa
    tay

    lda (tbladdr),y
    bpl .set

.v_loop:
    tya
    clc
    adc bgsize
    tay

    cpy lastidx
    bpl .bingo

    lda (tbladdr),y
    bmi .v_loop
    bpl .set

;=====horizontal=====
.horizontal
    ldy lastidx

.set_x:
    ldx bgsize
.h_loop:
    lda (tbladdr),y
    bpl .dec_y

    dey
    dex
    bne .h_loop

    lda #1
    sta vret
    rts

.dec_y
    stx vtmp

    tya
    sec
    sbc vtmp
    tay

    bpl .set_x

.ret
    lda #0
    sta vret
    rts
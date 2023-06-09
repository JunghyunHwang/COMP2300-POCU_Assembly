MARK_CALLED=%10000000
callednum=$00
vret=$01
vtmp=$10
LEN=25
table=$80

;=================
;====callednum====
;=================
callnum:
    .SUBROUTINE

    lda callednum
    ldx #LEN-1

.loop:
    cmp table,x
    beq .set_bit

    dex
    bpl .loop

    rts

.set_bit:
    ora #MARK_CALLED
    sta table,x
    rts

;=================
;=======won=======
;=================
won:
    .SUBROUTINE
;=====diagonal=====
    ldx #4
    lda table,x
    bpl .diagonal

    ldy #5
.rl_loop
    dey
    beq .bingo

    txa
    clc
    adc #4
    tax

    lda table,x
    bmi .rl_loop

.diagonal
    ldx #0
    lda table,x
    bpl .vertical

    ldy #5
.lr_loop
    dey
    beq .bingo

    txa
    clc
    adc #6
    tax

    lda table,x
    bmi .lr_loop

    jmp .vertical

.bingo
    lda #$01
    sta vret
    rts

;=====vertical=====
.vertical
    ldy #4

.set
    tya
    bmi .horizontal

    tax
    dey

.v_loop
    lda table,x
    bmi .chk_bingo

    jmp .set

.chk_bingo:
    txa
    clc
    adc #5
    tax

    cpx #LEN-1
    bpl .bingo
    
    lda table,x 
    bmi .chk_bingo

    jmp .set

;=====horizontal=====
.horizontal
    ldx #LEN-1

.set_y:
    ldy #5
.h_loop:
    lda table,x
    bpl .dec_x
    
    dex
    dey
    bne .h_loop

    lda #1
    sta vret
    rts

.dec_x:
    sty vtmp

    txa
    sec
    sbc vtmp
    tax
    
    bpl .set_y

.ret
    lda #0
    sta vret
    rts
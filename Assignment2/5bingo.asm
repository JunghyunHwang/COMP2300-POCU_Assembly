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

    inx
    inx
    inx
    inx

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

    inx
    inx
    inx
    inx
    inx
    inx

    lda table,x
    bmi .lr_loop

    jmp .vertical

.bingo
    lda #$01
    sta vret
    rts

;=====vertical=====
.vertical
    ldx #5
    stx vtmp

.set
    ldx vtmp
    dex
    bmi .horizontal
    stx vtmp

    ldy #5
    
.v_loop
    lda table,x
    bmi .chk_bingo

    jmp .set

.chk_bingo:
    dey
    beq .bingo
    inx
    inx
    inx
    inx
    inx
    
    lda table,x
    bmi .chk_bingo

    jmp .set

;=====horizontal=====
.horizontal
    ldx #LEN-1

.set_y:
    ldy #5
.h_loop:
    txa
    bmi .ret

    lda table,x
    bpl .dec_x
    
    dex
    dey
    bne .h_loop

    lda #1
    sta vret
    rts

.dec_x:
    dex
    dey
    bne .dec_x
    beq .set_y

.ret
    lda #0
    sta vret
    rts
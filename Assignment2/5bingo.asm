MARK_CALLED=%10000000
callednum=$00
vret=$01
vtmp=$10

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

    ldx #LEN-1

.set_y:
    ldy #5
.h_loop:
    txa
    bmi .vertical

    lda table,x
    bpl .dec_x
    
    dex
    dey
    bne .h_loop

    lda #$01
    sta vret
    rts

.dec_x:
    dex
    dey
    bne .dec_x
    beq .set_y

;=====vertical=====
.vertical
    ldx #$05
    stx vtmp

.set
    ldx vtmp
    dex
    bmi .ret
    stx vtmp

    ldy #$05
    
.v_loop
    lda table,x
    bmi .chk

    jmp .set

.chk:
    dey
    beq .bingo
    inx
    inx
    inx
    inx
    inx
    
    lda table,x
    bmi .chk

    jmp .set

.bingo
    lda #$01
    sta vret
    rts

.ret
    lda $00
    sta vret
    rts
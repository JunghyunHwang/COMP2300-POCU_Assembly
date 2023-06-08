    .PROCESSOR 6502
    .ORG $8000

LEN=25
table=$80
    .INCLUDE "utils/utils.asm"

    ldx #$FF
    txs

    ;===DEFINE BINGO TABLE HERE===
    .SUBROUTINE
    ldx #LEN
    ldy #LEN-1
.loop:
    stx table,y
    dex
    dey
    bpl .loop
    ;=============================

    lda #$19
    sta $00
    jsr callnum

    assert $0098, $99

    lda #$01
    sta $00
    jsr callnum

    assert $0080, $81

    lda #$20
    sta $00
    jsr callnum

    lda #$12
    sta $00
    jsr callnum

    assert $0091, $92

    lda #$13
    sta $00
    jsr callnum

    assert $0092, $93

    assert $0001, $00

    lda #$10
    sta $00
    jsr callnum

    lda #$11
    sta $00
    jsr callnum

    lda #$14
    sta $00
    jsr callnum

    termin
    
    .INCLUDE "5bingo.asm"

    .ORG $FFFC,0
    .WORD $8000
    .WORD $0000
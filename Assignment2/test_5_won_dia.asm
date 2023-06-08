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

    lda $80
    eor #MARK_CALLED
    sta $80

    lda $86
    eor #MARK_CALLED
    sta $86

    lda $8C
    eor #MARK_CALLED
    sta $8C

    lda $92
    eor #MARK_CALLED
    sta $92

    lda $98
    eor #MARK_CALLED
    sta $98

    jsr won

    assert $0001, $01

    lda $80
    eor #MARK_CALLED
    sta $80

    lda $86
    eor #MARK_CALLED
    sta $86

    lda $8C
    eor #MARK_CALLED
    sta $8C

    lda $92
    eor #MARK_CALLED
    sta $92

    lda $98
    eor #MARK_CALLED
    sta $98

    lda $84
    eor #MARK_CALLED
    sta $84

    lda $88
    eor #MARK_CALLED
    sta $88

    lda $8C
    eor #MARK_CALLED
    sta $8C

    lda $90
    eor #MARK_CALLED
    sta $90

    lda $94
    eor #MARK_CALLED
    sta $94

    jsr won

    assert $0001, $01

    lda $84
    eor #MARK_CALLED
    sta $84

    lda $88
    eor #MARK_CALLED
    sta $88

    lda $8C
    eor #MARK_CALLED
    sta $8C

    lda $90
    eor #MARK_CALLED
    sta $90

    lda $94
    eor #MARK_CALLED
    sta $94

    jsr won

    assert $0001, $00
    
    termin
    
    .INCLUDE "5bingo.asm"

    .ORG $FFFC,0
    .WORD $8000
    .WORD $0000
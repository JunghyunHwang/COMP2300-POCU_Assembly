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

    ; 주소: $0080
    ; $01,$02,$83,$04,$05
    ; $06,$07,$88,$09,$0A
    ; $0B,$0C,$8D,$0E,$0F
    ; $10,$11,$92,$13,$14
    ; $15,$16,$97,$18,$19

    lda #MARK_CALLED
    eor $96
    sta $96

    lda #MARK_CALLED
    eor $91
    sta $91

    lda #MARK_CALLED
    eor $8C
    sta $8C

    lda #MARK_CALLED
    eor $87
    sta $87

    lda #MARK_CALLED
    eor $82
    sta $82

    jsr won

    assert $0001, $01

    lda #MARK_CALLED
    eor $82
    sta $82

    jsr won

    assert $0001, $00

    termin
    
    .INCLUDE "5bingo.asm"

    .ORG $FFFC,0
    .WORD $8000
    .WORD $0000
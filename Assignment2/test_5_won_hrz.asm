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
    ; $01,$02,$03,$04,$05
    ; $06,$07,$08,$09,$0A
    ; $0B,$0C,$0D,$0E,$0F
    ; $90,$91,$92,$93,$94
    ; $15,$16,$17,$18,$19

    lda #MARK_CALLED
    eor $8F
    sta $8F

    lda #MARK_CALLED
    eor $90
    sta $90

    lda #MARK_CALLED
    eor $91
    sta $91

    lda #MARK_CALLED
    eor $92
    sta $92

    lda #MARK_CALLED
    eor $93
    sta $93

    jsr won

    assert $0001, $01

    lda #MARK_CALLED
    eor $8E
    sta $8E

    lda #MARK_CALLED
    eor $93
    sta $93

    jsr won

    assert $0001, $00

    termin
    
    .INCLUDE "5bingo.asm"

    .ORG $FFFC,0
    .WORD $8000
    .WORD $0000
    .PROCESSOR 6502
    .ORG $8000
    .INCLUDE "utils/utils.asm"

    ldx #$FF
    txs

    lda #2
    sta $10
    lda #4
    sta $11

    jsr max

    stx $0020

    assert $0020, $04

    lda #$0A
    sta $10
    lda #2
    sta $11

    jsr max

    stx $0020

    assert $0020, $0A

    lda #$0A
    sta $10
    lda #$0A
    sta $11

    jsr max

    stx $20

    assert $0020, $0A

    termin
    
    .INCLUDE "math.asm"

    .ORG $FFFC,0
    .WORD $8000
    .WORD $0000
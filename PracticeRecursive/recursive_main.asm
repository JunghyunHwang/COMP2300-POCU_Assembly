    .PROCESSOR 6502
    .ORG $8000

ret=$00
pnum=$20
    .INCLUDE "utils/utils.asm"

    ldx #$FF
    txs

    lda #3
    sta pnum

    jsr sum

    assert $0020, $06

    .INCLUDE "recursive.asm"

    termin

    .ORG $FFFC,0
    .WORD $8000
    .WORD $0000
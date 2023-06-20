    .PROCESSOR 6502
    .ORG $8000

MAX=10
vtmp=$80
    .INCLUDE "utils/utils.asm"

    ldx $FF
    txs
    
    lda #0
    sta vtmp
    ldx #MAX
    clc

.loop
    txa
    adc vtmp
    sta vtmp

    dex
    bne .loop

    assert $0080, $37

    termin

    .ORG $FFFC,0
    .WORD $8000
    .WORD $0000
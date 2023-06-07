    .PROCESSOR 6502
    .ORG $8000
    .INCLUDE "utils/utils.asm"

    ldx #$FF
    txs

    lda #2
    pha
    lda #4
    pha

    jsr min

    pla
    pla

    assert $0020, $02

    termin
    
    .INCLUDE "math.asm"

    .ORG $FFFC,0
    .WORD $8000
    .WORD $0000
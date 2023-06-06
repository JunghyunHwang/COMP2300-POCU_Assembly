    .PROCESSOR 6502
    .ORG $8000
    .INCLUDE "utils/utils.asm"

    ldx #$FF
    txs

    pha
    pha
    lda #4
    pha
    lda #2
    pha

    jsr minmax

    pla
    sta $20
    assert $0020, $02

    pla
    sta $20
    assert $0020, $04

    pha
    pha
    lda #2
    pha
    lda #4
    pha

    jsr minmax

    pla
    sta $20
    assert $0020, $02

    pla
    sta $20
    assert $0020, $04

    pha
    pha
    lda #10
    pha
    lda #9
    pha

    jsr minmax

    pla
    sta $20
    assert $0020, $09

    pla
    sta $20
    assert $0020, $0A

    termin
    
    .INCLUDE "math.asm"

    .ORG $FFFC,0
    .WORD $8000
    .WORD $0000
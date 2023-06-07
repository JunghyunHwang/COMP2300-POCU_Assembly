    .PROCESSOR 6502
    .ORG $8000

LEN=25
table=$80
    .INCLUDE "utils/utils.asm"

    ldx #$FF
    txs

    lda #>$2301
    pha
    lda #<$2301
    pha
    lda #>$2300
    pha
    lda #<$2300
    pha
    lda #4
    pha
    lda #2
    sta $10

    jsr mmref

    assert $2300, $02
    assert $2301, $04

    lda #>$2301
    pha
    lda #<$2301
    pha
    lda #>$2300
    pha
    lda #<$2300
    pha
    lda #2
    pha
    lda #4
    sta $10

    jsr mmref

    assert $2300, $02
    assert $2301, $04

    termin
    
    .INCLUDE "math.asm"

    .ORG $FFFC,0
    .WORD $8000
    .WORD $0000
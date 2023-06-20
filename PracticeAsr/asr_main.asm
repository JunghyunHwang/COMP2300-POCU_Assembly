    .PROCESSOR 6502
    .ORG $8000

src=$00
out=$01
    .INCLUDE "utils/utils.asm"

    ldx #$FF
    txs

    lda #$F6
    sta src

    jsr asr

    assert $0001, $FB

    lda #$0A
    sta src

    jsr asr

    assert $0001, $05

    termin

    .INCLUDE "asr.asm"

    .ORG $FFFC,0
    .WORD $8000
    .WORD $0000
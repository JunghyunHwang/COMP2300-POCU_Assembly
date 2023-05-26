ina=$4000
inb=$4004
out=$2300

    .PROCESSOR 6502
    .ORG $8000

    clc
    lda #$0A
    sta ina
    lda #$06
    sta inb

    lda ina
    adc inb
    sta out

    lda ina+1
    adc inb+1
    sta out+1

    lda ina+2
    adc inb+2
    sta out+2

    lda ina+3
    adc inb+3
    sta out+3

    .ORG $FFFC,0
    .WORD $8000
    .WORD $0000
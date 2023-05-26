ina=$4000
inb=$4004
out=$2300
    ldx #$FF
    txs

    clc
    lda ina
    sbc inb
    sta out

    lda ina+1
    sbc inb+1
    sta out+1

    lda ina+2
    sbc inb+2
    sta out+2

    lda ina+3
    sbc inb+3
    sta out+3
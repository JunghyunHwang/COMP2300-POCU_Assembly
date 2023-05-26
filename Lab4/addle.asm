ina=$4000
inb=$4004
out=$2300
    ldx #$FF
    txs

    clc
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
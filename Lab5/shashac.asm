buffer=$C000
out=$2300
count=$1000
    ldx #$FF
    txs

    lda #0
    sta out
    sta out+1
    sta out+2
    sta out+3
    
    lda buffer
    clc
    adc buffer
    adc buffer
    adc buffer
    sta count

round:
    ldx #0

accum:
    lda out
    eor buffer+2,x
    sta out

    lda out+1
    eor buffer+3,x
    sta out+1

    lda out+2
    eor buffer+4,x
    sta out+2

    lda out+3
    eor buffer+5,x
    sta out+3

    inx
    inx
    inx
    inx
    cpx count
    bcc accum

check:
    lda out
    and buffer+1
    beq continue
    
    lda out+1
    and buffer+1
    beq continue

    lda out+2
    and buffer+1
    beq continue

    lda out+3
    and buffer+1
    bne end

continue:
    asl out
    rol out+1
    rol out+2
    rol out+3

    lda out
    ora #1
    sta out

    lda out+1
    ora #1
    sta out+1

    lda out+2
    ora #1
    sta out+2

    lda out+3
    ora #1
    sta out+3

    jmp round

end:
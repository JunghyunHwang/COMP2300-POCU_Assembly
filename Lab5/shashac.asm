buffer=$C000
out=$2300
size=$0010
check_bit=size+1
count=$0020
    ldx #$FF
    txs

    lda #0
    sta out
    sta out+1
    sta out+2
    sta out+3
    
    lda buffer+1
    sta check_bit

    lda buffer
    sta size
    clc
    adc size
    adc size
    adc size
    sta count

round:
    ldx count

accum:
    lda out+3
    eor buffer+1,x
    sta out+3
    dex

    lda out+2
    eor buffer+1,x
    sta out+2
    dex

    lda out+1
    eor buffer+1,x
    sta out+1
    dex

    lda out
    eor buffer+1,x
    sta out
    dex
    
    bne accum

check:
    lda out
    and check_bit
    beq continue
    
    lda out+1
    and check_bit
    beq continue

    lda out+2
    and check_bit
    beq continue

    lda out+3
    and check_bit
    bne end

continue:
    lda #1
    asl out
    ora out
    sta out

    lda #1
    rol out+1
    ora out+1
    sta out+1

    lda #1
    rol out+2
    ora out+2
    sta out+2
    
    lda #1
    rol out+3
    ora out+3
    sta out+3

    jmp round

end:
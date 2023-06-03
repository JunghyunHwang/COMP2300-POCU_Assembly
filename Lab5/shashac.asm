buffer=$C000
out=$2300
count=$0010
check_bit=count+1
temp_out=$0020

    ldx #$FF
    txs

    lda #0
    sta temp_out
    sta temp_out+1
    sta temp_out+2
    sta temp_out+3
    
    lda buffer+1
    sta check_bit

    lda buffer
    clc
    adc buffer
    adc buffer
    adc buffer
    sta count
round:
    ldx count

accum:
    lda temp_out+3
    eor buffer+1,x
    sta temp_out+3
    dex

    lda temp_out+2
    eor buffer+1,x
    sta temp_out+2
    dex

    lda temp_out+1
    eor buffer+1,x
    sta temp_out+1
    dex

    lda temp_out
    eor buffer+1,x
    sta temp_out
    dex
    
    bne accum

check:
    lda temp_out
    and check_bit
    beq continue
    
    lda temp_out+1
    and check_bit
    beq continue

    lda temp_out+2
    and check_bit
    beq continue

    lda temp_out+3
    and check_bit
    bne end

continue:
    asl temp_out
    rol temp_out+1
    rol temp_out+2
    rol temp_out+3

    lda temp_out
    ora #1
    sta temp_out

    lda temp_out+1
    ora #1
    sta temp_out+1

    lda temp_out+2
    ora #1
    sta temp_out+2

    lda temp_out+3
    ora #1
    sta temp_out+3

    jmp round

end:
    lda temp_out
    sta out

    lda temp_out+1
    sta out+1

    lda temp_out+2
    sta out+2

    lda temp_out+3
    sta out+3
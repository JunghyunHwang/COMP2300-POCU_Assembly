maskcarry=%00000001
maskzero=%00000010
maskover=%01000000
masknegative=%10000000
out=$2303
temp=$0020

    php
    pla
    sta temp

    lda temp
    and #maskcarry
    sta out

    lda temp
    and #maskzero
    lsr
    sta out-1

    lda temp
    and #maskover
    lsr
    lsr
    lsr
    lsr
    lsr
    lsr
    sta out-2

    lda temp
    and #masknegative
    lsr
    lsr
    lsr
    lsr
    lsr
    lsr
    lsr
    sta out-3
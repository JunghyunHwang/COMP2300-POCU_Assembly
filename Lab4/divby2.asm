masknegative=%10000000
in=$4003
out=$2303

    ldx #$FF
    txs

    lda in
    php
    ror
    sta out
    pla
    and #masknegative
    ora out
    sta out

    lda in
    ror

    lda in-1
    ror
    sta out-1

    lda in-2
    ror
    sta out-2

    lda in-3
    ror
    sta out-3
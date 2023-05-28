masknegative=%10000000
in=$4003
out=$2303

testin=$4013
testout=$2313

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

    ;Test positive number
    lda testin
    php
    ror
    sta testout
    pla
    and #masknegative
    ora testout
    sta testout

    lda testin
    ror

    lda testin-1
    ror
    sta testout-1

    lda testin-2
    ror
    sta testout-2

    lda testin-3
    ror
    sta testout-3
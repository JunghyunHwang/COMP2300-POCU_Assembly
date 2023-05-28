masknegative=%10000000
in=$4003
out=$2303

    ldx #$FF
    txs

    lda in
    and #masknegative
    tax
    lda in
    ror
    sta out
    txa
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
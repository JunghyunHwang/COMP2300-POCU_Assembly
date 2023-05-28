NUM=%00010111    
    .PROCESSOR 6502
    .ORG $8000

    ldx #$FF
    txs

    php
    lda #NUM
    php

    .ORG $FFFC,0
    .WORD $8000
    .WORD $0000
    .PROCESSOR 6502
    .ORG $8000

ret=$00
    .INCLUDE "utils/utils.asm"

    ; calc
    .MACRO calc ;(a,b)
        .IFNCONST OP
            clc
            lda {1}
            adc {2}

            sta ret
        .ELSE
            .IF OP=1
                sec
                lda {1}
                sbc {2}

                sta ret
            .ELSE
                lda {1}
                ldx {2}
                
loop:
                dex
                beq exit

                adc {1}
                jmp loop

exit:
                sta ret
            .ENDIF
        .ENDIF
    .ENDM

    ldx #$FF
    txs

    calc #$0A, #$03
    
    termin

    .ORG $FFFC,0
    .WORD $8000
    .WORD $0000
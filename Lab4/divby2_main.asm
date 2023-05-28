    .PROCESSOR 6502
    .ORG $8000

    .INCLUDE "utils/utils.asm"

    ;===DEFINE INPUT HERE===
    ; 0xFFFFFB2E (-1234)
    lda #$2E
    sta $4000
    lda #$FB
    sta $4001
    lda #$FF
    sta $4002
    lda #$FF
    sta $4003

    lda #$15
    sta $4010
    lda #$CD
    sta $4011
    lda #$5B
    sta $4012
    lda #$07
    sta $4013
    ;========================

    .INCLUDE "divby2.asm"

    ;===DEFINE ASSERTIONS HERE===
    assert $2300, $97
    assert $2301, $FD
    assert $2302, $FF
    assert $2303, $FF

    assert $2310, $8A
    assert $2311, $E6
    assert $2312, $AD
    assert $2313, $03
    ;============================

    termin

end:
	jmp end

    .ORG $FFFC,0
    .WORD $8000
    .WORD $0000
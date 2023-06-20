    .PROCESSOR 6502
    .ORG $8000
LEN=enums-nums
MAGIC=1
ret=$00
    .INCLUDE "utils/utils.asm"

	ldx #LEN
loop:
	dex
	bmi check

	txa
	and #MAGIC
	beq step

	jmp loop

step:
	clc
	lda nums,x
	adc ret
    sta ret

	jmp loop

check:

    assert $0000, $24
	
    termin

	.ORG $C000
nums:
	.BYTE $01,$02,$03,$04
	.BYTE $05,$06,$07,$08
	.BYTE $09,$0A,$0B,$0C
enums:

    .ORG $FFFC,0
    .WORD $8000
    .WORD $0000
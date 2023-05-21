#include <stdio.h>
#include "disassembler.h"

static const char* mnemonics[256] = { "brk i", "ora (zp,x)", "", "", "", "ora zp", "asl zp", "", "php i", "ora #", "asl A", "", "", "ora a", "asl a", "", "bpl r", "ora (zp),y", "", "", "", "ora zp,x", "asl zp,x", "", "clc i", "ora a,y", "", "", "", "ora a,x", "asl a,x", "", "jsr a", "and (zp,x)", "", "", "bit zp", "and zp", "rol zp", "", "plp i", "and #", "rol A", "", "bit a", "and a", "rol a", "", "bmi r", "and (zp),y", "", "", "", "and zp,x", "rol zp,x", "", "sec i", "and a,y", "", "", "", "and a,x", "rol a,x", "", "rti i", "eor (zp,x)", "", "", "", "eor zp", "lsr zp", "", "pha i", "eor #", "lsr A", "", "jmp a", "eor a", "lsr a", "", "bvc r", "eor (zp),y", "", "", "", "eor zp,x", "lsr zp,x", "", "cli i", "eor a,y", "", "", "", "eor a,x", "lsr a,x", "", "rts i", "adc (zp,x)", "", "", "", "adc zp", "ror zp", "", "pla i", "adc #", "ror A", "", "jmp (a)", "adc a", "ror a", "", "bvs r", "adc (zp),y", "", "", "", "adc zp,x", "ror zp,x", "", "sei i", "adc a,y", "", "", "", "adc a,x", "ror a,x", "", "", "sta (zp,x)", "", "", "sty zp", "sta zp", "stx zp", "", "dey i", "", "txa i", "", "sty a", "sta a", "stx a", "", "bcc r", "sta (zp),y", "", "", "sty zp,x", "sta zp,x", "stx zp,y", "",  "tya i", "sta a,y", "txs i", "", "", "sta a,x", "", "", "ldy #", "lda (zp,x)", "ldx #", "", "ldy zp", "lda zp", "ldx zp", "", "tay i", "lda #", "tax i", "", "ldy a", "lda a", "ldx a", "", "bcs r", "lda (zp),y", "", "", "ldy zp,x", "lda zp,x", "ldx zp,y", "", "clv i", "lda a,y", "tsx i", "", "ldy a,x", "lda a,x", "ldx a,y", "",  "cpy #", "cmp (zp,x)", "", "", "cpy zp", "cmp zp", "dec zp", "", "iny i", "cmp #", "dex i", "", "cpy a", "cmp a", "dec a", "", "bne r", "cmp (zp),y", "", "", "", "cmp zp,x", "dec zp,x", "", "cld i", "cmp a,y", "", "", "", "cmp a,x", "dec a,x", "", "cpx #", "sbc (zp,x)", "", "", "cpx zp", "sbc zp", "inc zp", "", "inx i", "sbc #", "nop i", "", "cpx a", "sbc a", "inc a", "", "beq r", "sbc (zp),y", "", "", "", "sbc zp,x", "inc zp,x", "", "sed i", "sbc a,y", "", "", "", "sbc a,x", "inc a,x", "" };

const unsigned char* disassemble(char* out_buffer64, const unsigned char* mem)
{
    const char* mnemonic = mnemonics[mem[0]];

    if (mnemonic[4] == 'A' || mnemonic[4] == 'i') {
        char high_bit[3];
        char low_bit[3];

        high_bit[0] = '.';
        high_bit[1] = '.';
        high_bit[2] = '\0';

        low_bit[0] = '.';
        low_bit[1] = '.';
        low_bit[2] = '\0';

        sprintf(out_buffer64, "OPCODE=%02X[%s] OPERAND=%s %s", mem[0], mnemonic, high_bit, low_bit);

        ++mem;
    } else if (mnemonic[4] == 'a' || mnemonic[5] == 'a') {
        unsigned char low_bit = *++mem;
        unsigned char high_bit = *++mem;

        sprintf(out_buffer64, "OPCODE=%02X[%s] OPERAND=%02X %02X", mem[0], mnemonic, high_bit, low_bit);

        ++mem;
    } else {
        unsigned char low_bit = *++mem;

        sprintf(out_buffer64, "OPCODE=%02X[%s] OPERAND=.. %02X", mem[0], mnemonic, low_bit);

        ++mem;
    }
    
    return mem;
}
TITLE Stat Printer

.DOSSEG
.8086
.8087
.MODEL TINY

.DATA

.CODE
.STARTUP
    mov ah, 4Ch
    xor al, al
    int 21h

END
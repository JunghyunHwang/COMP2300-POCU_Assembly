TITLE Stat Printer

.DOSSEG
.8086
.8087
.MODEL TINY

FILENAME EQU 13

.DATA
input_msg DB "Enter a file name",0Dh,0Ah,'$'
file_name DB FILENAME
          DB FILENAME+1 DUP (?)

file_handle DW ?
scnds_type DB ?
scnds DD ?


.CODE
.STARTUP
    printstr MACRO str
        lea dx, str
        mov ah, 09h
        int 21h
    ENDM

    printstr input_msg

    ; Read file name
    lea dx, file_name
    mov ah, 0Ah
    int 21h

    lea bx, file_name
    mov dh, 00h
    mov dl, BYTE PTR [bx+1]
    mov si, dx
    mov al, 0h
    mov BYTE PTR [bx+2+si], al

    ; File open
    mov ax, 3D00h
    lea dx, file_name[2]
    int 21h

    mov file_handle, ax

    ; Read file
    mov bx, file_handle
    mov cx, 01h
    lea dx, scnds_type
    mov ah, 3Fh
    int 21h

    ; Read file
    mov bx, file_handle
    mov cx, 04h
    lea dx, scnds
    mov ah, 3Fh
    int 21h

    fld scnds
    
    mov ah, 4Ch
    xor al, al
    int 21h

END
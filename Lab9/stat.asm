TITLE Stat Printer

.DOSSEG
.8086
.8087
.MODEL TINY

FILENAME EQU 0Dh
MILLI EQU 006Dh
MICRO EQU 0075h

.DATA
input_msg DB "Enter a file name",0Dh,0Ah,'$'
file_name DB FILENAME
          DB FILENAME+1 DUP (?)

float_str DB "00.000$"

seconds_type DB ?
to_alpha DB 30h
result DW ?
file_handle DW ?
data_cnt DW 0
to_micro DW 1000
to_milli DW 1000
seconds DQ ?

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

    ; Read seconds type
    mov bx, file_handle
    mov cx, 01h
    lea dx, seconds_type
    mov ah, 3Fh
    int 21h

    finit
    fldz
    fwait

    mov ah, 00h
    mov al, seconds_type
    cmp ax, MICRO
    jz read_loop_micro

read_loop_milli:
    mov bx, file_handle
    mov cx, 08h
    lea dx, seconds
    mov ah, 3Fh
    int 21h

    cmp ax, 00h
    jz calc_avg

    fld seconds
    fimul to_micro
    fadd
    fwait

    inc data_cnt
    jmp read_loop_milli

read_loop_micro:
    mov bx, file_handle
    mov cx, 08h
    lea dx, seconds
    mov ah, 3Fh
    int 21h

    cmp ax, 00h
    jz calc_avg

    fadd seconds
    fwait

    inc data_cnt
    jmp read_loop_micro

calc_avg:
    fidiv data_cnt
    fidiv to_milli
    fistp result

    fwait

    mov si, 06h
    lea bx, float_str
loop_itoa:
    dec si
    jb print_str

    cmp si, 02h
    jz loop_itoa

    mov ax, 0Ah
    div result
    mov result, ax

    add dl, to_alpha
    mov BYTE PTR [bx+si], dl

    jmp loop_itoa

print_str:
    printstr float_str

    mov ah, 4Ch
    xor al, al
    int 21h

END
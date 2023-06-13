include 'macros.inc'
; Using modified Borland fastcall calling convention
; Callees clear registers and stack they use themselves, caller cleans up the stack

use16
org 100h

    call get_mode
    mov [mode_before_start], ax
    call set_vga_x_mode
    fastcall screen_fill, 125
    mov ah, 8h
    int 21h
    fastcall set_standart_mode, [mode_before_start]
    ret

include 'vgax.inc'

mode_before_start dw 0

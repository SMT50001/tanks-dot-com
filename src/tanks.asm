include 'macros.inc'
; Using cdecl calling convention
use16
org 100h

    call get_mode
    mov [mode_before_start], al
    call set_vga_x_mode
    mov ah, 8h
    int 21h
    mov ah, 0
    mov al, [mode_before_start]
    cdecl set_standart_mode, ax
    ret

include 'vgax.inc'

mode_before_start db ?

include 'macros.inc'
; Using modified Borland fastcall calling convention
; Caller cleans up

use16
org 100h

    call get_mode
    mov [mode_before_start], ax
    call set_vga_x_mode
    fastcall set_palette, palette
    fastcall screen_fill, 0
    fastcall draw_square, 200, 50, 0x0100

    mov ah, 8h
    int 21h
    fastcall set_standart_mode, [mode_before_start]
    ret

include 'vgax.inc'
include 'gfxutil.inc'
include 'gfx.inc'

mode_before_start dw 0

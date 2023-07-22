include 'macros.inc'
; Using modified Borland fastcall calling convention
; Caller cleans up

use16
org 100h

    push cs
    pop ds

    call get_mode
    mov [mode_before_start], ax
    call set_vga_x_mode
    fastcall set_palette, palette
    fastcall screen_fill, 1

    .main_loop:
    call wait_retrace
    fastcall draw_sprite, 152, [sprite_pos], tank1_0
    call get_key
    cmp ah, 1
    je .exit
    cmp ah, 11h
    jne .dont_move_sprite
    fastcall draw_sprite, 152, [sprite_pos], tank3_3
    sub [sprite_pos], 16
    .dont_move_sprite:
    call flush_kbd_buf
    jmp .main_loop

    .exit:
    fastcall set_standart_mode, [mode_before_start]
    ret

include 'vgax.inc'
include 'gfxutil.inc'
include 'gfx.inc'
include 'input.inc'

mode_before_start dw 0

sprite_pos dw 224

include 'macros.inc'
; Using modified Borland fastcall calling convention
; Caller cleans up

use16
org 100h

    push cs
    pop ds

    call test_vga_card
    cmp ax, 0
    je .no_bios_support
    cmp ax, 1
    je .card_detect_failed

    call disable_kbd_int

    call get_mode
    mov [mode_before_start], ax
    call set_vga_x_mode
    fastcall set_palette, palette

    set_curr_vid_page 0
    fastcall plane_fill, 1

    ; Do logic
    .main_loop:
    call get_key
    cmp al, 1
    je .stop_loop
    cmp al, 11h
    jne .dont_move_sprite
    sub [sprite_pos], 1
    .dont_move_sprite:
    ; Wait for retrace and draw
    call wait_retrace
    fastcall redraw_sprite, 152, [sprite_pos], tank1_0
    jmp .main_loop

    .stop_loop:
    call enable_kbd_int
    fastcall set_standart_mode, [mode_before_start]
    jmp .exit

    .no_bios_support:
    mov dx, no_bios_support_msg
    jmp .errors

    .card_detect_failed:
    mov dx, no_vga_msg
    jmp .errors

    .errors:
    mov ah, 9h
    int 21h

    .exit:
    ret

include 'vgax.inc'
include 'gfxutil.inc'
include 'gfx.inc'
include 'input.inc'
include 'v_logic.inc'

mode_before_start dw 0
no_bios_support_msg db 13, 10, 'No BIOS support detected', 13, 10, '$'
no_vga_msg db 13, 10, 'No VGA card detected', 13, 10, '$'

sprite_pos dw 224

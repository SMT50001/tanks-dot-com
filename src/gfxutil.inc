; Various graphic utilities

define INPUT_STATUS 0x03da
define VRETRACE 0x08

; AX: X position; DX: Y position CH: type; CL: size
; No return value
; Draws a sprite
draw_square:
    mov bx, dx
    shl bx, 6
    shl dx, 4
    shr ax, 2
    add bx, ax
    add bx, dx

    mov dx, bx
    and dx, 3
    mov al, 1
    xchg dx, cx
    shl al, cl
    fastcall set_plane_write_mode, ax

    mov ax, VSTART
    mov es, ax
    mov [es:bx], dh
    ret

; AX: color
; No return value
; Fills video memory with single color
screen_fill:
    mov cx, ax

    fastcall set_plane_write_mode, 0x000f

    mov ax, VSTART
    mov es, ax
    mov di, 0
    mov ah, cl
    mov al, cl
    mov cx, VPSIZE/2
    rep stosw

    ret

; No arguments
; No return value
; Wait for screen retrace
wait_retrace:
    mov dx, INPUT_STATUS

    .wait_vert:
    in ax, dx
    and ax, VRETRACE
    test ax, 0
    jnz .wait_vert

    .wait_refresh:
    in ax, dx
    not ax
    and ax, VRETRACE
    test ax, 0
    jnz .wait_refresh

    ret

; Various graphic utilities

; AX: X position; DX: Y position CH: type; CL: size
; No return value
; Draws a sprite
draw_sprite:
    mov bx, dx
    shl bx, 6
    shl dx, 4
    shr ax, 2
    add bx, ax
    add bx, dx

    mov dx, bx
    and dx, 3
    mov al, 1
    xor dx, cx
    xor cx, dx
    xor dx, cx
    shl al, cl
    xor dx, cx
    xor cx, dx
    xor dx, cx
    fastcall set_plane_write_mode, ax

    mov ax, VSTART
    mov es, ax
    mov [es:bx], ch
    ret


; Various graphic utilities

define INPUT_STATUS 0x03da
define VRETRACE 0x08

; AX: X position; DX: Y position CX: sprite struct
; No return value
; Draws a sprite
draw_sprite:
    push cx
    add cx, 2
    mov si, cx

    push ax
    mov bx, dx
    shl bx, 6
    shl dx, 4
    shr ax, 2
    add ax, bx
    add ax, dx
    mov di, ax
    push ax

    cld
    xor dx, dx

    .draw_planes_loop:

    mov bx, sp
    mov ax, [bx+2]
    add ax, dx
    and ax, 3
    mov cx, ax
    xor ax, ax
    inc ax
    shl ax, cl
    push dx
    fastcall set_plane_write_mode, ax
    pop dx

    mov     ax, VSTART ; point ES to display memory
    mov     es, ax

    push di

    mov bx, sp
    xor cx, cx
    mov ax, [bx+6]
    mov bx, ax
    mov cl, [bx]
    shr cx, 2
    push cx
    xor ax, ax
    mov al, [bx+1]
    mov bx, sp

    .draw_columns_loop:

    push ax
    .draw_raws_loop:
    lodsb
    cmp al, 0
    je .transparent
    stosb
    jmp .non_transparent
    .transparent:
    inc di
    .non_transparent:
    loop .draw_raws_loop
    pop ax
    ; rep movsb, but with transparency

    mov cx, [bx]
    sub di, cx
    add di, W/4
    cmp ax, 0
    dec ax
    jne .draw_columns_loop

    pop cx
    pop di

    ;pop ax
    cmp dx, 3
    inc dx
    jbe .draw_planes_loop

    add sp, 6
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

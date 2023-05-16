; VGA Mode X setup routines

; No arguments
; No return value
; Sets video mode to mode X
set_vga_x_mode:
    push ax
    mov ax, 13h
    int 10h ; Setting mode 13h
    pop ax
    ret

; 1:word - mode to set
; No return value
; Sets one of the standart video modes
set_standart_mode:
    push ax
    push bx
    mov bx, sp
    mov ax, [bx+6]
    int 10h
    pop bx
    pop ax
    ret

; No arguments
; AL: video mode number
; Gets current video mode
get_mode:
    push ax
    mov ah, 0x0f
    int 10h
    pop ax
    ret

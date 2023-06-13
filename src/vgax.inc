; VGA Mode X setup routines

define MAP_MASK 0x02

define VSTART 0xa000
define VPSIZE 0x4b00
define W 320
define H 240

; No arguments
; No return value
; Sets video mode to mode X
set_vga_x_mode:

    fastcall set_standart_mode, 13h

    mov dx, 0x03c4
    mov ax, 0x0604
    out dx, ax ; Turn off the Chain-4 bit (bit 3 at index 4, port 0x3c4)

    mov dx, 0x03d4
    mov ax, 0xe317
    out dx, ax ; Turn off word mode, by setting the Mode Control register of the CRT Controller (index 0x17, port 0x03d4)

    mov dx, 0x03d4
    mov ax, 0x0014
    out dx, ax ; Turn off doubleword mode, by setting the Underline Location register (index 0x14, port 0x03d4)

    mov dx, 0x03c2
    mov al, 0xe3
    out dx, al ; Modify the vertical sync polarity bits in the Misc. Output Register to achieve square aspect ratio

    ; Modify the vertical timing registers to reflect the increased vertical resolution, and to center the image as good as possible
    mov dx, 0x03d4
    mov ax, 0x2c11
    out dx, ax ; turn off write protect
    mov ax, 0x0d06
    out dx, ax ; vertical total
    mov ax, 0x3e07
    out dx, ax ; overflow register
    mov ax, 0xea10
    out dx, ax ; vertical retrace start
    mov ax, 0xac11
    out dx, ax ; vertical retrace end AND wr.prot
    mov ax, 0xdf12
    out dx, ax ; vertical display enable end
    mov ax, 0xe715
    out dx, ax ; start vertical blanking
    mov ax, 0x0616
    out dx, ax ; end vertical blanking

    ret

; AX - mode to set
; No return value
; Sets one of the standart video modes
set_standart_mode:
    int 10h
    ret

; No arguments
; AX: video mode number
; Gets current video mode
get_mode:
    push bx
    mov ah, 0x0f
    int 10h
    pop bx
    mov ah, 0
    ret

; AX - color
; No return value
; Fills video memory with single color
screen_fill:

    push bx
    mov cx, ax

    mov dx, 0x03c4
    mov ax, 0x0f00 + MAP_MASK
    out dx, ax

    mov ax, VSTART
    mov es, ax
    mov di, 0
    mov ah, cl
    mov al, cl
    mov cx, VPSIZE/2
    rep stosw

    pop bx
    ret


crtparam:
.vert_tot dw 0x00d06
.overflow dw 0x03e07
.cell_height dw 0x04109
.vsync_start dw 0x0ea10
.vsync_end dw 0x0ac11
.display_vert dw 0x0df12
no_dword dw 0x00014
vblank_start dw 0x0e715
vblank_end dw 0x00616
byte_mode dw 0x0e317


; No arguments
; No return value
; Disables keyboard interrupts
disable_kbd_int:
    in al, 21h
    or al, 2h
    out 21h, al
    ret

enable_kbd_int:
    in al, 21h
    sub al, 2h
    out 21h, al
    ret

; No arguments
; AL: Keyboard scan code
; Reads character from keyboard buffer
get_key:
    mov al, 0x0a          ; select IRR
    out 20h, al
    in al, 20h           ; get IRR
    test al, 02h         ; check if IRQ1
    jz .no_key

    in al, 60h    ; read keyboard buffer
    mov dl, al

    in al, 61h    ; get system crtl port
    mov ah, al
    or al, 80h    ; reset keyboard
    out 61h, al
    mov al, ah    ; rewrite original byte
    out 61h, al

    mov al, dl
    jmp .exit
    .no_key:
    mov al, 0
    .exit:
    ret


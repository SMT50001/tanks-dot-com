; No arguments
; AH: Keyboard scan code, AL: ASCII value of keypress (0 if extended ASCII), AX = 0 if no key is waiting, ZF = set if no key in buffer (AX = 0) clear if a key was found (AX = key)
; reads character from keyboard buffer
get_key:
    mov ah,1 ;Service 1 (Keystroke waiting?)
    int 16h ;Do It
    jz @f ;If no key waiting, we're done
    xor ah, ah ;If a key is waiting, service 0 (Get keystroke)
    int 16h ;Do It
    jmp .done ;We're done
    @@: ;No keystroke waiting
    xor ax, ax ;Make sure AX=0
    .done: ;We're done
    or ax,ax ;Set the found/not found flag
    ret

flush_kbd_buf:
    push ax ;Save used registers
    @@: ;Loop to here for each key
    call get_key ;Get a key from the keyboard buffer
    jnz @b ;If there was one, get another
    pop ax ;Restore used registers
    ret

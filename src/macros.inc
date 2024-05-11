macro fastcall proc, arg_ax, arg_dx, arg_cx, [arg]
{
    if ~ arg_ax eq ax
        if ~ arg_ax eq
            mov ax, word arg_ax
        end if
    end if
    if ~ arg_dx eq dx
        if ~ arg_dx eq
            mov dx, word arg_dx
        end if
    end if
    if ~ arg_cx eq cx
        if ~ arg_cx eq
            mov cx, word arg_cx
        end if
    end if
    common
        size@fastcall = 0
    if ~ arg eq
    reverse
        push word arg
        size@fastcall = size@fastcall + 2
    common
    end if
        call proc
    if size@fastcall
        add sp, size@fastcall
    end if
}

define PAGE_ZERO 0xa000
define PAGE_ONE 0xa4b0
define PAGE_TWO 0xa960

macro set_curr_vid_page pagenum
{
    if pagenum eq 0
        mov     ax, PAGE_ZERO
        mov     es, ax
    end if
    if pagenum eq 1
        mov     ax, PAGE_ONE
        mov     es, ax
    end if
    if pagenum eq 1
        mov     ax, PAGE_TWO
        mov     es, ax
    end if
}

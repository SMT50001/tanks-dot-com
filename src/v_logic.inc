; Video drawing logic

redraw_sprite:
    fastcall copy_to_vmem_arbitrary_masked, ax, dx, cx
    ret

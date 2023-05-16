mkdir build
del /Q build\*.*
fasm-win\fasm src\tanks.asm build\tanks.com -s build\tanks.fas

#!/usr/bin/env python

from PIL import Image
import glob
import pathlib
import os

# list and read images for processing
files = glob.glob('res/*.png')
images = [(os.path.splitext(pathlib.Path(filename).name)[0], Image.open(filename).getdata()) for filename in files]

# todo work with not just png (RGBA)

# generate palette
listOfLists = [image for (name, image) in images]
pixels = [pixel for image in listOfLists for pixel in image]
colors = [(pixel[0], pixel[1], pixel[2]) for pixel in pixels]
uniqueColors = set(colors)
palette = [(255,0,255), (0,0,0)] + list(uniqueColors)

# checks that A in RGBA is either 0 or 255 in the image
assert len([x for x in pixels if x[3] != 0 and x[3] != 255]) == 0

def format_asm_array(name, iterable):
    return f'{name}_length dw {len(iterable)}' + '\n' + f'{name} db {format_asm_array_body(iterable)}'

def format_palette(palette):
    return f'palette_colors dw {format_asm_array_length_hex(len(palette))}' + '\n' + f'palette db {format_asm_array_body([color for rgb in palette for color in rgb])}'

def format_asm_array_length_hex(x):
    return '0x%02x'%x + '00'

def format_asm_array_body(iterable):
    return ', '.join([str(x) for x in iterable])

with open('src/gfx.inc', 'w') as out:
    out.write(format_palette(palette))
    out.write('\n')
    for (name, image) in images:
        colorIndices = [0 if a == 0 else palette.index((r, g, b)) for (r, g, b, a) in image]
        out.write(format_asm_array(name, colorIndices))
        out.write('\n')

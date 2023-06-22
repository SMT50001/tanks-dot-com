#!/usr/bin/env python

from PIL import Image
import glob
import pathlib
import os

# list and read images for processing
files = glob.glob('res/*.png')
images = [(os.path.splitext(pathlib.Path(filename).name)[0], Image.open(filename)) for filename in files]

# todo work with not just png (RGBA)

# generate palette
listOfImageData = [image.getdata() for (name, image) in images]
pixels = [pixel for image in listOfImageData for pixel in image]
colors = [(pixel[0], pixel[1], pixel[2]) for pixel in pixels]
uniqueColors = set(colors)
palette = [(255,0,255), (0,0,0)] + list(uniqueColors) + [(0,0,0)]*(256 - 2 - len(uniqueColors))

# checks that A in RGBA is either 0 or 255 in the image
assert len([x for x in pixels if x[3] != 0 and x[3] != 255]) == 0

def format_asm_array(name, iterable, image):
    return f'{name}:' + '\n' + f'{name}_size db {image.width}, {image.height}' + '\n' + f'{name}_pix db {format_asm_array_body(iterable)}'

def format_palette(palette):
    return f'palette db {format_asm_array_body([color for rgb in palette for color in rgb])}'

def format_asm_array_body(iterable):
    return ', '.join([str(x) for x in iterable])

def reshuffle(initialList):
    return initialList[0::4] + initialList[1::4] + initialList[2::4] + initialList[3::4]

with open('src/gfx.inc', 'w') as out:
    out.write(format_palette(palette))
    out.write('\n')
    for (name, image) in images:
        colorIndices = [0 if a == 0 else palette.index((r, g, b)) for (r, g, b, a) in image.getdata()]
        colorIndicesReshuffled = reshuffle(colorIndices)
        out.write(format_asm_array(name, colorIndicesReshuffled, image))
        out.write('\n')

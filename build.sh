#!/bin/sh

cd "${0%/*}"
mkdir build
rm build/tanks.com
fasm src/tanks.asm build/tanks.com

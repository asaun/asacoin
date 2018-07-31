#!/bin/bash
# create multiresolution windows icon
ICON_SRC=../../src/qt/res/icons/asacoin.png
ICON_DST=../../src/qt/res/icons/asacoin.ico
convert ${ICON_SRC} -resize 16x16 asacoin-16.png
convert ${ICON_SRC} -resize 32x32 asacoin-32.png
convert ${ICON_SRC} -resize 48x48 asacoin-48.png
convert asacoin-16.png asacoin-32.png asacoin-48.png ${ICON_DST}


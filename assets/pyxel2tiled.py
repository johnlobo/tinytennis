# Converter from pyxel edit to tiled
# -*- coding: utf-8 -*-

import csv
import sys
import os

if (len(sys.argv) == 1):
    print("Pyxel Edit file needed")
    sys.exit()

print('Transforming the file '+ os.path.basename(sys.argv[1]) + ' into tmx format\n')

nameFile = os.path.splitext(sys.argv[1])[0]

fileIn = open(sys.argv[1], 'r', encoding='UTF-8')
dataIn = fileIn.readlines()

tileswide = dataIn[0].split()[1]
tileshigh = dataIn[1].split()[1]
tileswidth = dataIn[2].split()[1]
tilesheight = dataIn[3].split()[1]

fileOut = open(nameFile + ".tmx", 'w', encoding='UTF-8')
fileOut.write('<?xml version="1.0" encoding="UTF-8"?>\n')
fileOut.write('<map version="1.0" tiledversion="1.0.2" orientation="orthogonal"'
              ' renderorder="left-up" width="' + tileswide + '" height="' + tileshigh + '" tilewidth="' + tileswidth +
              '" tileheight="' + tilesheight + '" nextobjectid="1">\n')
fileOut.write('<tileset firstgid="1" source="tennis.tsx"/>\n')
fileOut.write('<layer name="Tile Layer 1" width="' + tileswide + '" height="' + tileshigh + '">\n')
fileOut.write('<data encoding="csv">\n')

i = 6
while i < (len(dataIn[6:]) + 6):
    data = dataIn[i].split(',')
    newLine = ''
    j = 0
    while j < len(data):
        if data[j].isdigit():
            number = int(data[j]) + 1
            newLine += str(number)
            if not((i == (len(dataIn[6:]) - 2 + 6)) and (j == len(data)-2)):
                newLine += ','
        j+= 1
    newLine = newLine + '\n'
    fileOut.write(newLine)
    i += 1

fileOut.write('</data>\n')
fileOut.write('</layer>\n')
fileOut.write('</map>\n')
fileOut.close()
print("The file "+nameFile+'.tmx has been generated\n')
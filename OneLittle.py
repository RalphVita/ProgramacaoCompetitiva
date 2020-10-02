import re
import sys

#Lista de Entradas
lst = []
for line in sys.stdin:
    lst.append(line.rstrip("\n"))

#Tranforma tudo em lista de inteiro
regex = [[int(r) for r in re.findall("^[-+]?[0-9]+$",line)]
            for line in lst]

convert = lambda x : x#(((x << 24) & 0xFF000000) | ((x <<  8) & 0x00FF0000) | ((x >>  8) & 0x0000FF00) | ((x >> 24) & 0x000000FF))

[print(convert(r[0])) for r in regex]


import re
import sys

#Lista de Entradas
lst = []
for line in sys.stdin:
    lst.append(line.rstrip("\n"))


regex = [[int(r) for r in re.findall("(\d+)",line)]
            for line in lst]

convert = lambda x: '+'.join([str(y) for y in sorted(x)]) 

[print(convert(r)) for r in regex]
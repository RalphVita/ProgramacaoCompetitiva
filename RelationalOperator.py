import re
import sys

#Lista de Entradas
lst = []
for line in sys.stdin:
    lst.append(line.rstrip("\n"))

#Tranforma tudo em lista de inteiro
regex = [[int(r) for r in re.findall("(\d+)",line)]
            for line in lst]
t = regex[0]
convert = lambda y: "<" if y < 0 else (">" if y > 0 else "=") 
[print(convert(r[0]-r[1])) for  r in regex[1:t[0]+1]]

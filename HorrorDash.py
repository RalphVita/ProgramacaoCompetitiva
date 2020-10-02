import re
import sys

#Lista de Entradas
lst = []
for line in sys.stdin:
    lst.append(line.rstrip("\n"))

#Tranforma tudo em lista de inteiro
regex = [[int(r) for r in re.findall("(\d+)",line)]
            for line in lst]

#Máxima velocidade de cada caso
cases = [max(r[1:]) for r in regex[1:]]

#Imprime
for i in range(0,regex[0][0]):
    print('Case',str(i+1)+":",cases[i])
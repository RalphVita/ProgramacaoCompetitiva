import re
import sys

def array_to_string(l):
    s = ''
    for i in l:
        s += str(i)
    return s

#Lista de Entradas
lst = []
for line in sys.stdin:
    lst.append(line.rstrip("\n"))

#Tranforma tudo em lista de inteiro
regex = [[int(r) for r in re.findall("(\d+)",line)]
            for line in lst]

for r in regex:
    n = [int(i) for i in list(str(r[0]))]
    i = r[1]
    while i > 0:
        #print("---------------")
        #print(n)
        j = 0
        
        #while j < len(n) and i+1+j < (len(n)) and n[j:i+1+j].index(max(n[j:i+1+j])) == 0:
        while j < len(n)-1  and n[j:min(len(n), i+1+j)].index(max(n[j:min(len(n), i+1+j)])) == 0:
            j += 1
        #print(j)
        j = n[j:min(len(n), i+1+j)].index(max(n[j:min(len(n), i+1+j)]))+j
        if(j > 0):
            if n[j] > n[j-1]:  
                aux = n[j]
                n[j] = n[j-1]
                n[j-1] = aux
        i -= 1
        #print(n)
        #print("---------------")
    print(array_to_string(n))
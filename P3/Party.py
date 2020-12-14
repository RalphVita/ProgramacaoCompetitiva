#Baseado em https://github.com/krishnakeshav/codeforces-solutions/blob/master/115A.cpp
#Busca a maior distancia entre o um funcionário e o chefão
def Read():
    line = input()
    while line == '':
        line = input()
    return line.strip()

n = int(Read())
e = [int(Read()) for i in range(n)] 
altura = 0

for i in range(n-1):
    count = 0
    x = e[i+1]
    while x != -1:
        x = e[x-1]
        count += 1
    altura = max(altura,count)

print(altura+1)
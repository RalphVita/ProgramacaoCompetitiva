N = int(input())
Hs = [int(k) for k in input().split(' ')]

# F[i] é o menor custo de 0 até i
F = [0]*N
F[0] = 0
F[1] = abs(Hs[1]-Hs[0])

def Custo(atual, anterior):
    global Hs, F
    return F[anterior] + abs(Hs[atual]-Hs[anterior])

for i in range(2,N):
    F[i] =  min(Custo(i,i-1), Custo(i,i-2))
    
print(F[-1])
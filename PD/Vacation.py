N = int(input())
Ps = [[int(k) for k in input().split(' ')] for i in range(N)]
F=[]

def Max(dia,exluir_atividade):
    return max(F[dia][:exluir_atividade]+F[dia][exluir_atividade+1:])


# F[i,j] é a maior felicidade no i, se fizer a atividade j
F = [[0]*3 for _ in range(N)]

F[0] = Ps[0]

for i in range(1,N):
    F[i] =  [Ps[i][j]+Max(i-1,j) for j in range(3)]
#Comentário
print(max(F[-1]))
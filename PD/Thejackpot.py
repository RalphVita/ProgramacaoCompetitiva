def Apostar(N, A):
    # F[i] é a maior soma em apostas até i
    F = [0]*N
    F[0] = max(A[0],0)

    for i in range(1,N):
        F[i] =  max(A[i]+F[i-1], A[i])
        
    return max(F)

def Read():
    line = input()
    while line == '':
        line = input()
    return line.strip()

N = int(Read())
while N > 0:
    
    A = [int(k) for k in Read().split(' ')]
    while len(A) < N:
        A += [int(k) for k in Read().split(' ')]
    if(max(A) <= 0):
        print('Losing streak.')
    else:
        _max = Apostar(N,A)
        print('The maximum winning streak is '+str(_max)+'.')

    N = int(Read())
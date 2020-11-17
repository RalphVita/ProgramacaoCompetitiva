s = list(input())
n = int(input())

size = len(s)
F = [0]*size
#F[i] é a quantidade de si==s(i+1) em S até i
F[0] = 0
_min = 1
def SetarF(_max):
    global F, _min
    for i in range(_min,_max):
        F[i] = F[i-1] + (1 if s[i] == s[i-1] else 0)

for i in range(n):
    l, r = tuple([int(x) for x in input().split(' ')])
    if(_min < r):
        SetarF(r)
    print(F[r-1]-F[l-1])

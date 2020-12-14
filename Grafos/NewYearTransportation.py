n, t = tuple([int(x) for x in input().split(' ')])
P = [int(x) for x in input().split(' ')]

i = 0
#Caminha até t
while i < t - 1: 
    i += P[i]

#Verifica se chegou
print(('YES' if i == t - 1 else 'NO'))

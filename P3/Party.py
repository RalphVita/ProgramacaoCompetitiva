n = int(input())
s = {}
for x in range(n):
    v = int(input())
    if(v not in s):
        s[v] = []
    s[v].append(x+1)

print(s)
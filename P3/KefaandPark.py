n, m = tuple([int(x) for x in input().split(' ')])
hasgato = [int(x) for x in input().split(' ')]

G =[]

vis = [False]*n
ans = 0

def dfs(c,v):
    global vis, ans, G, m, hasgato
    vis[v] = True

    #Verifica gatos consecutivos
    c += hasgato[v]
    if (not hasgato[v]):
        c = 0
    if (c > m):
         return
        
        
    f = False
    for i in range(len(G[v])):
        t = G[v][i]
        if (not vis[t]):
            dfs(c, t) 
            f = True
    
    if (not f):
        ans += 1



for i in range(n):
    G.append([])

#Ler vetices
for i in range(1,n):
    u, v = tuple([int(x) for x in input().split(' ')])
    G[u-1].append(v-1)
    G[v-1].append(u-1)

#DFS
dfs(0, 0)
print(ans)
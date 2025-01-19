#include <iostream>

#include <bits/stdc++.h>
using namespace std;
 
// utility function to form edge between two vertices
// source and dest
void add_edge(vector<int> adj[], int src, int dest)
{
    adj[src].push_back(dest);
    adj[dest].push_back(src);
}
 
// a modified version of BFS that stores predecessor
// of each vertex in array p
// and its distance from source in array d
bool BFS(vector<int> adj[], int src, int dest, int v,
         int pred[], int dist[])
{
    // a queue to maintain queue of vertices whose
    // adjacency list is to be scanned as per normal
    // DFS algorithm
    list<int> queue;
 
    // boolean array visited[] which stores the
    // information whether ith vertex is reached
    // at least once in the Breadth first search
    bool visited[v];
 
    // initially all vertices are unvisited
    // so v[i] for all i is false
    // and as no path is yet constructed
    // dist[i] for all i set to infinity
    for (int i = 0; i < v; i++) {
        visited[i] = false;
        dist[i] = INT_MAX;
        pred[i] = -1;
    }
 
    // now source is first to be visited and
    // distance from source to itself should be 0
    visited[src] = true;
    dist[src] = 0;
    queue.push_back(src);
 
    // standard BFS algorithm
    while (!queue.empty()) {
        int u = queue.front();
        queue.pop_front();
        for (int i = 0; i < adj[u].size(); i++) {
            if (visited[adj[u][i]] == false) {
                visited[adj[u][i]] = true;
                dist[adj[u][i]] = dist[u] + 1;
                pred[adj[u][i]] = u;
                queue.push_back(adj[u][i]);
 
                // We stop BFS when we find
                // destination.
                if (adj[u][i] == dest)
                    return true;
            }
        }
    }
 
    return false;
}
 
// utility function to print the shortest distance
// between source vertex and destination vertex
void printShortestDistance(vector<int> adj[], int s,
                           int dest, int v)
{
    // predecessor[i] array stores predecessor of
    // i and distance array stores distance of i
    // from s
    int pred[v], dist[v];
 
    if (BFS(adj, s, dest, v, pred, dist) == false) {
        cout << "Given source and destination"
             << " are not connected";
        return;
    }
 
    // vector path stores the shortest path
    vector<int> path;
    int crawl = dest;
    path.push_back(crawl);
    while (pred[crawl] != -1) {
        path.push_back(pred[crawl]);
        crawl = pred[crawl];
    }
 
    // distance from source is in distance array
    cout //<< "Shortest path length is : "
         << dist[dest] << endl;
 
    // printing path from source to destination
    // cout << "\nPath is::\n";
    // for (int i = path.size() - 1; i >= 0; i--)
    //     cout << path[i] << " ";
}


int mapa[1000][1000];
int bomb[1000000];
  
// Driver program to test methods of graph class 
int main() 
{ 
    int R,C,r,c,index,rows,rn,cn,n, dR,dC;
    

    while (cin >> R >> C)
    {
        if (R == 0)
            break;
        
        int v = R*C;
        vector<int> adj[v]; 

        
        //Mapeia linhas e colunas
        index = 0;
        for(r=0;r<R;r++){
            for(c=0;c<C;c++){
                mapa[r][c] = index;
                bomb[index] = 0;
                index++;
            }
        }

        //Identificar minas
        cin >> rows;
        for(;rows > 0;--rows){
            cin >> rn >> n;
                for(;n > 0;--n){
                    cin >> cn;
                    bomb[mapa[rn][cn]] = 1;
                }
        }

        for(r=0;r<R;r++)
            for(c=0;c<C;c++){
                    if(bomb[mapa[r][c]] == 0){
                        if(c + 1 < C && bomb[mapa[r][c+1]] == 0)
                            add_edge(adj,mapa[r][c],mapa[r][c+1]);
                        if(c - 1 >= 0 && bomb[mapa[r][c-1]] == 0)
                            add_edge(adj,mapa[r][c],mapa[r][c-1]);
                        if(r + 1 < R && bomb[mapa[r+1][c]] == 0)
                            add_edge(adj,mapa[r][c],mapa[r+1][c]);
                        if(r - 1 >= 0 && bomb[mapa[r-1][c]] == 0)
                            add_edge(adj,mapa[r][c],mapa[r-1][c]);
                    }
            }
        
        cin >> R >> C;
        cin >> dR >> dC;

        printShortestDistance(adj, mapa[R][C],mapa[dR][dC], v); 
    }
    
  
    return 0; 
} 
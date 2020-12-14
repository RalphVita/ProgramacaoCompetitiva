#include <iostream>

// A C++ program for Bellman-Ford's single source 
// shortest path algorithm. 
#include <bits/stdc++.h> 
  using namespace std; 
// a structure to represent a weighted edge in graph 
struct Edge { 
    int src, dest, weight; 
}; 
  
// a structure to represent a connected, directed and 
// weighted graph 
struct Graph { 
    // V-> Number of vertices, E-> Number of edges 
    int V, E; 
  
    // graph is represented as an array of edges. 
    struct Edge* edge; 
}; 
  
// Creates a graph with V vertices and E edges 
struct Graph* createGraph(int V, int E) 
{ 
    struct Graph* graph = new Graph; 
    graph->V = V; 
    graph->E = E; 
    graph->edge = new Edge[E]; 
    return graph; 
} 
  
// A utility function used to print the solution 
void printArr(int dist[], int n) 
{ 
    printf("Vertex   Distance from Source\n"); 
    for (int i = 0; i < n; ++i) 
        printf("%d \t\t %d\n", i, dist[i]); 
} 

// The main function that finds shortest distances from src to 
// all other vertices using Bellman-Ford algorithm.  The function 
// also detects negative weight cycle 
void BellmanFord(struct Graph* graph, int src, int destino) 
{ 
    int V = graph->V; 
    int E = graph->E; 
    int dist[V]; 
  
    // Step 1: Initialize distances from src to all other vertices 
    // as INFINITE 
    for (int i = 0; i < V; i++) 
        dist[i] = INT_MAX; 
    dist[src] = 0; 
  
    // Step 2: Relax all edges |V| - 1 times. A simple shortest 
    // path from src to any other vertex can have at-most |V| - 1 
    // edges 
    for (int i = 1; i <= V - 1; i++) { 
        for (int j = 0; j < E; j++) { 
            int u = graph->edge[j].src; 
            int v = graph->edge[j].dest; 
            int weight = graph->edge[j].weight; 
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) 
                dist[v] = dist[u] + weight; 
        } 
    } 
  
    // Step 3: check for negative-weight cycles.  The above step 
    // guarantees shortest distances if graph doesn't contain 
    // negative weight cycle.  If we get a shorter path, then there 
    // is a cycle. 
    for (int i = 0; i < E; i++) { 
        int u = graph->edge[i].src; 
        int v = graph->edge[i].dest; 
        int weight = graph->edge[i].weight; 
        if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) { 
            //printf("Graph contains negative weight cycle"); 
            cout << "Impossible" << endl;
            return; // If negative cycle is detected, simply return 
        } 
    } 

    if(dist[destino] == INT_MAX)
         cout << "Impossible" << endl;
     else
         cout << dist[destino] << endl;
  
    //printArr(dist, V); 
  
    return; 
} 

  
// Driver program to test methods of graph class 
int main() 
{ 
    int N =  0,M,Q,u,v,w;
    int m,q,i,j;
    int d;
    int inicio = 1;
    struct Graph* graph;
    
    while(!cin.eof()){
        
        cin >> N >> M >> Q;

        if(N > 0 && inicio == 0)
            cout << endl;
        
        inicio = 0;
        
        graph = createGraph(N, M); 

        if(N == 0)
            return 0;

        for(m = 0;m < M; m++){
                cin >> u >> v >> w;
                graph->edge[m].src = u; 
                graph->edge[m].dest = v; 
                graph->edge[m].weight = w;
        }

        //for (i = 0; i < N; i++)
            

        for(;Q > 0; --Q){
            cin >> u >> v;
            BellmanFord(graph,u, v);
            //d = dist[u][v];
            // if(d < 0)
            //     cout << "Impossible" << endl;
            // else if (d == INT_MAX)
            //     cout << "Impossible" << endl;
            // else
            //     cout << d << endl;
            
        }
        

                
    }
     
  
    return 0; 
} 
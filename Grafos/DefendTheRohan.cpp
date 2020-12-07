#include <iostream>
#define V 50

using namespace std; 

int g[V][V];
int dist[V][V]; 
  
void floydWarshall (int N)  
{  
    /* dist[][] will be the output matrix  
    that will finally have the shortest  
    distances between every pair of vertices */
    int  i, j, k;  
  
    /* Initialize the solution matrix same  
    as input graph matrix. Or we can say  
    the initial values of shortest distances 
    are based on shortest paths considering  
    no intermediate vertex. */
    for (i = 0; i < N; i++)  
        for (j = 0; j < N; j++)  
            dist[i][j] = g[i][j];  
  
    /* Add all vertices one by one to  
    the set of intermediate vertices.  
    ---> Before start of an iteration,  
    we have shortest distances between all  
    pairs of vertices such that the  
    shortest distances consider only the  
    vertices in set {0, 1, 2, .. k-1} as 
    intermediate vertices.  
    ----> After the end of an iteration,  
    vertex no. k is added to the set of  
    intermediate vertices and the set becomes {0, 1, 2, .. k} */
    for (k = 0; k < N; k++)  
    {  
        // Pick all vertices as source one by one  
        for (i = 0; i < N; i++)  
        {  
            // Pick all vertices as destination for the  
            // above picked source  
            for (j = 0; j < N; j++)  
            {  
                // If vertex k is on the shortest path from  
                // i to j, then update the value of dist[i][j]  
                if (dist[i][k] + dist[k][j] < dist[i][j])  
                    dist[i][j] = dist[i][k] + dist[k][j];  
            }  
        }  
    }  
  
}  
  
// Driver program to test methods of graph class 
int main() 
{ 
    int T,N,b,a,R,s,d,w, sum;

    cin >> T;
    for (int t = 1; t <= T; ++t) {
        cin >> N;
        b = a = 0;
        for(;a < N; a++){
            b = 0;
            for(;b < N; b++){
                cin >> w;
                g[a][b] = w; 
            }
        }
        floydWarshall(N);
        cin >> R;
        sum = 0;
        for(;R > 0; --R){
            cin >> s >> d;
            sum += dist[s-1][d-1];
        }
        

        cout << "Case #" << t << ": " << sum << endl;        
    }
     
  
    return 0; 
} 
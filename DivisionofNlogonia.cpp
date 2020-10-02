#include <iostream>
using namespace std;

int main(){
    int K;
    int N, M;
    int X, Y;
    bool valido;
    int valor = 0, _valor;
    while (true)
    {
        cin >> K;
        if(!K)
            return 0;
        cin >> N >> M;
        for(int k = 0; k < K; k++){
            cin >> X >> Y;
            if (X == N || X == M || Y == N || Y ==M)
                cout << "divisa" << endl; 
            else
                if(X < N)
                    if(Y < M)
                        cout << "SO" << endl;
                    else
                        cout << "NO" << endl;
                else
                    if(Y < M)
                        cout << "SE" << endl;
                    else
                        cout << "NE" << endl;
        }
        
    }
}

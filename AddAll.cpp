#include <iostream>
#include <queue>
using namespace std;

int main(){
        int N, x,cost = 0, sum;
        
        //Vetor ordenado de inteiros
        priority_queue<int, vector<int>, greater<int> >q; 
        //Inpirado em https://gist.github.com/KT-Yeh/9286314
        //A principio tentei com um vetor. Após carrega-lo, ordenava ascendente e começaca o calculo de custo.
        //Mas no meio dos calculos observei que os custos também precisavam ser ordenados, para entrar no calculo novamente.
        //Ou seja, precisava de uma outra estrutura, e não um vetor, dai veio a fila de prioridade.
        
        while (!cin.eof())
        {
            if(cin >> N){
                if(N == 0)
                    return 0;
                
                //Armazena ordenadamente
                for (int n = 0; n < N; ++n)
                {
                    cin >> x;
                    q.push(x);
                }

                sum = 0;
                cost = 0;

                //Calcula os custos e colocar o resultado na lista ordenada, para ser somado novamente
                while (true)
                {
                    cost =  q.top();
                    q.pop();
                    cost += q.top();
                    q.pop();
                    sum += cost;

                    if(q.empty())
                        break;

                    q.push(cost);
                }
                
                cout << sum << endl;

            }
        }
}
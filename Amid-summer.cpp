#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <utility>
#include <set>
#include <numeric>
using namespace std;

int Minimizar(vector<int> &v, int a, map<int,pair<set<int>,int>> &map, int &minSum){
    int sum = 0;
    for (auto x: v){
        sum += abs(x-a);
    }
    //A partir do momento que a soma é maior, todas outras serão
    if(sum > minSum)
        return 0;
    map[sum].first.insert(a);//Registra A ordernado nessa soma
    map[sum].second++;//Quantas vezes deu essa soma
    minSum = min(sum,minSum);

    return 1;
}

void Minimizar(vector<int> v){
    map<int,pair<set<int>,int>> map;
    int A, countA = 0, totalA;
    int sum = 0, minSum = INT32_MAX;

    //Reparei que as minimas somas estão em torno da média
    int mean = std::accumulate(v.begin(), v.end(), 0.0)/v.size();
    //E se for interando A do minimo até o máximo, as somas vão diminuindo,
    //em torna da média é minima, e depois aumenta
    
    //Busca da média pra cima, e para quando acha uma soma maior que a minima
    for (int a = mean; a <= *max_element(v.begin(),v.end()) ; ++a)
    {
        if(!Minimizar(v,a,map,minSum))
            break;
    }
    //Busca da média pra baixo e para quando acha uma soma maior que a minima
    for (int a = mean-1; a >= *min_element(v.begin(),v.end()); --a)
    {
        if(!Minimizar(v,a,map,minSum))
            break;
    }
    //Menor A
    A = *map.begin()->second.first.begin();
    
    //Quantos da entrada tem a soma minima
    for (auto s: map.begin()->second.first)
        countA += count(v.begin(), v.end(),s); 
    
    //Quantos inteiros satisfazem A
    totalA = map.begin()->second.second;
    cout << A << " " << countA << " " << totalA << endl;
}
int main(){
        int n,x;
        vector<int> v;
        while (!cin.eof())
        {
            if(cin >> n){
                for (int i = 0; i < n; ++i)
                {
                    cin >> x;
                    v.push_back(x);
                }
                Minimizar(v);
                v.clear();
            }
        }
}

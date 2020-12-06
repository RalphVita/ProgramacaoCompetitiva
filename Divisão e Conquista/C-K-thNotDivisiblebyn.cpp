#include <iostream>

using namespace std;

int Verificar(int n,int k){
    int i;
    int mod;
    if (k < n)
        return k;
    //Cresce de (n-1) em (n-1)
    i = (k/(n-1))*n;
    k -= (n-1)*(k/(n-1));
    
    while (k > 0){
        mod = i % n;
        if (mod != 0){
            k -= 1;
            i++;
        }
        else
            i += (n-mod);
    }
    return i-1;
    //return i + (k > 0 ? 1 : -1);
}

int main(){
        int N;
        
        int n,k;
        
        cin >> N;
        while (N > 0 &&!cin.eof())
        {
            cin >> n >> k;
            cout << Verificar(n,k) << endl;
            N--;
        }
}
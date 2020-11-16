#include <iostream>

using namespace std;

int Baixaria(int n,int k){
    int i;
    if (k < n)
        return k;
    //Cresce de (n-1) em (n-1)
    i = (k/(n-1))*n;
    k -= (n-1)*(k/(n-1));
    while (k > 0){
        if (i % n != 0)
            k -= 1;
        i += 1;
    }
    return i-1;
}

int main(){
        int N;
        
        int n,k, need;
        
        cin >> N;
        while (N > 0 &&!cin.eof())
        {
            cin >> n >> k;
            need = (k - 1) / (n - 1);
            cout << need + k << endl;
            N--;
        }
}
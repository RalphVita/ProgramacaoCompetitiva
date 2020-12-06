#include <iostream>

using namespace std;
int F[100000];
int main(){
        string S;
        int n, i;
        int l,r;
        F[0] = 0;
        
        
        cin >> S;
        
        for(i=1; i < S.size(); i++)
            F[i] = F[i-1] + (S[i] == S[i-1] ? 1 : 0);
            
        cin >> n;
        while (n > 0 &&!cin.eof())
        {
            cin >> l >> r;
            cout << (F[r-1]-F[l-1]) << endl;
            n--;
        }
}
#include <iostream>
#include <vector>
using namespace std;

int main(){
        int n,x;
        int soma[200] = {};
        int countL = 0,countC = 0;
        int l,c;
        
        while (!cin.eof())
        {
            if(cin >> n){
                if(n == 0)
                    return 0;
                
                //Armazena ordenadamente
                for (int i = 0; i < n; ++i)
                {
                    for (int j = 0; j < n; ++j){
                        cin >> x;
                        soma[i] += x;
                        soma[j+n] += x;
                    }
                }
                countL = countC = 0;
                for (size_t i = 0; i < 200; i++)
                    if(soma[i] % 2 != 0)
                    {
                        if(i >= n){
                            countC++;
                            c = i-n+1;
                        }
                        else{
                            countL++;
                            l = i+1;
                        }
                    }
                
                if(countC == 0 && countL == 0)
                    cout << "OK" << endl;
                else if(countC == 1 && countL == 1)
                    cout << "Change bit (" << l << "," << c << ")" <<  endl;
                else{
                    cout << "Corrupt" << endl;
                }
                for (size_t i = 0; i < 200; i++)
                    soma[i] = 0;
            }
        }
}
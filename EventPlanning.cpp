#include <iostream>
using namespace std;

int main(){

    int n,b,w,h;
    int p,a;
    bool valido;
    int valor = 0, _valor;
    while (!cin.eof())
    {
        valor = INT32_MAX;
        cin >> n >> b >> h >> w;
        for(int i = 0; i < h; i++){
            cin >> p;
            valido = false;
            for (int j = 0; j < w; j++)
            {
                cin >> a;
                valido =  (a >= n) || valido;
            }

            if(valido){
                _valor = n * p;
                if(_valor < valor){
                    if(_valor <= b)
                        valor = _valor;
                }
            }
        }
        if (valor == INT32_MAX )
            cout <<  "stay home" << endl;
        else
            cout <<  valor << endl;
        
    }
    return 0;
}

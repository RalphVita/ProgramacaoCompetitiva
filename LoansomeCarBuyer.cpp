#include <iostream>

using namespace std;

int main(){
    int MESES, LINHAS;
    double PARCELA , TOTAL;
    int M,M_ANTERIOR;
    double P;
    double valor, divida; 
    bool done = false;
    while (true)
    {
        cin >> MESES >> PARCELA >> TOTAL >> LINHAS;
        if(MESES < 0)
            return 0;
        
        divida = TOTAL;
        M_ANTERIOR = -1;
        M = 0;
        done = false;
        cout << "--------------" << endl;
        cin >> M_ANTERIOR >> P;
        for(int m = 1; m < MESES; m++){

            
            if(M - m == 1 && LINHAS){
                
                
                cin >> M;
                
                --LINHAS;
            }
            
            if(m == 0)
                valor = (TOTAL + PARCELA)*(1-P);
            else{
                valor = valor *(1-P);
                divida = divida - PARCELA;
            }
            
            
            cout << valor << " " << divida << endl;
            if(divida < valor && !done){
                cout << m << " month" << (m <= 1 ? "":"s") << endl;
                done = true;
            }
            

        }
        
    }
}

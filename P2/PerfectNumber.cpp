#include <iostream>

using namespace std;
int F[100000];



int main(){
        
        int n, count = 0, i = 18, aux,sum;
    
        cin >> n;
        
        
        while (count < n)
        {
            i++;
            aux = i;
            sum = 0;
            while(aux > 0){
                sum +=aux%10;
                aux /= 10;
                
            }
            if(sum == 10)
                count++;
        }
        cout << i << endl;
}
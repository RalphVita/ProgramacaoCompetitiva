#include <iostream>
using namespace std;
//Swap32 eu encontrei como sujestão em:
//https://stackoverflow.com/questions/27506474/how-to-byte-swap-a-32-bit-integer-in-python
int main(){
        int n,nc;
        while (!cin.eof())
        {
            if(cin >> n){
            //Swap32
            nc = (((n << 24) & 0xFF000000) | ((n << 8) & 0x00FF0000) | ((n >> 8) & 0x0000FF00) | ((n >> 24) & 0x000000FF));
            cout << n << " converts to " << nc << endl;
            }
        }
}

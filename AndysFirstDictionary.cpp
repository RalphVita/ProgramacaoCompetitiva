#include <iostream>
#include <set>
#include <algorithm>
#include <regex>
using namespace std;

int main(){
    string word;
    set<string> palavras;

    //Letras
    regex regexpLetras("[a-z]+");

    while (!cin.eof())
        if(cin >> word){
            transform(word.begin(), word.end(), word.begin(), ::tolower); 

            std::sregex_iterator iter(word.begin(), word.end(), regexpLetras);
            std::sregex_iterator end;
            
            while(iter != end)
            {
                for(unsigned i = 0; i < iter->size(); ++i)
                    palavras.insert((*iter)[i]);
                ++iter;
            }
        }
    for(auto p: palavras)
        cout << p << endl;
    return 0;
}

#include <iostream>
#include <set>
#include <algorithm>
#include <regex>
using namespace std;

int main(){
    string word, word2;
    set<string> palavras;

    //Letras
    regex regexpLetras("[a-z\-]+");
    smatch match; 

    while (!cin.eof())
        if(cin >> word){

            word2 = word;
            while(word2.back() == '-'){
                cin >> word2;
                word=word.substr(0, word.size()-1) + word2;
            }

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

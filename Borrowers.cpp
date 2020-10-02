#include <iostream>
#include <algorithm>
#include <set>
#include <map>
#include <regex>
using namespace std;

int main(){
        string line, cmd, title;
        //<Titulo,Status>
        // Status: 0: Na bibliota, 1:Emprestado, 2 : Devolvido mas ainda não foi reposto
        map<string,int> livros;
        map<string,set<string>> autor_livros;
        vector<string> vetLivros;
        
        //Busca pelo titulo e autor do livro na linha
        regex regexpTitleAutor("(\".+\") by (.+)$");
        smatch match; 

        while(true){
            getline(cin, line);
            if(line == "END")
                break;
            regex_search(line, match, regexpTitleAutor); 
            livros[match[1]] = 0;
            autor_livros[match[2]].insert(match[1]);
        }
        //Gera um vetor ordenado de livros
        for(auto m : autor_livros)
            for(auto l: m.second)
                vetLivros.push_back(l);

        //Lê os comandos
        regex regexpComando ("(\".+\")");
        while(true){
            cin >> cmd;
            if(cmd == "END"){
                
                break;
            }
            if(cmd == "SHELVE"){

                for (auto livro=vetLivros.begin(); livro!=vetLivros.end(); ++livro){
                    int &status = livros[*livro];
                    if(status == 2){
                        cout << "Put " << *livro;

                        auto livro_anterior = livro;
                        
                        if(livro_anterior != vetLivros.begin())
                            livro_anterior--;
                        while(livros[*livro_anterior] != 0 && livro_anterior != vetLivros.begin()){livro_anterior--;}
                        if(livro_anterior == vetLivros.begin() && livros[*livro_anterior] != 0){
                            cout << " first" <<endl;
                        }else
                            cout  << " after " << *livro_anterior << endl;
                        
                        status = 0;
                            
                    }
                }
                cout << "END" << endl;  
            }
            else{
                getline(cin, title);
                regex_search(title, match, regexpComando);
                // 1:Emprestado, 2 : Devolvido mas ainda não foi reposto
                livros[match[0]] = cmd == "BORROW" ? 1 : 2; 
            }
        }
}


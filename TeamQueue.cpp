#include <iostream>
#include <queue>
#include <map>
using namespace std;

int main(){
    int t,size, item,group, scenario = 0,element;
    string cmd;
    std::map<int,int> mapItemGroup;

    map<int,queue<int>> qByGroup;
    queue<queue<int>*> qq;
    while (true)
    {
        cin >> t;
        if(!t)
            return 0;
        
        cout << "Scenario #" << ++scenario << endl;
        
        //Mapeia os itens por grupo
        for(int group = 0; group < t; ++group){
            cin >> size;
            for (int j = 0; j < size; ++j){
                cin >> element;
                mapItemGroup[element] = group;
            }
        }
        
        while (true)
        {
            cin >> cmd;
            if (cmd == "STOP"){
                cout << endl;
                break;
            }
            else if(cmd == "ENQUEUE"){
                cin >> item;
                group = mapItemGroup[item]; //Pega o grupo do item
                qByGroup[group].push(item); //Adciona o item na fila do grupo
                if(qByGroup[group].size() == 1)
                    qq.push(&qByGroup[group]); //Adciona a fila do grupo na fila de filas, por referência
                
            }
            else{
                //Pega o primeiro elemento da primeira fila
                cout << qq.front()->front() << endl;
                qq.front()->pop();//Remove o individuo
                if(qq.front()->empty())
                    qq.pop();//Se essa fila já foi toda, remove ela da fila de fila
            }
        }
        //Limpa essa bagunça
        while(!qq.empty()){
            while(!qq.front()->empty()) 
                qq.front()->pop();
            qq.pop();
        }
    }
}

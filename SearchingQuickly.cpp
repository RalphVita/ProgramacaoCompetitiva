#include <iostream>
#include <algorithm>
#include <sstream>
#include <queue>
#include <map>
#include <set>
using namespace std;

int main(){
    
    string str, line, copy;
    map<string,vector<string>> map;
    set<string> ignore;
    int position = 0;
    
    while (true)
    {
        cin >> str;
        if(str == "::")
            break;
        ignore.insert(str);
    }
    while (!cin.eof())
    {
        std::getline(cin, line);
        transform(line.begin(), line.end(), line.begin(), ::tolower); 
        std::istringstream iss(line);
        position = 0;
        while (iss >> str) { 
            if(ignore.find(str) == ignore.end()){
                copy = line;
                transform(&copy[position], &copy[position+str.size()], &copy[position], ::toupper); 
                map[str].push_back(copy);
            }
            position+= str.size()+1;
        }  
    }
    for (auto m: map)
        for(auto t: m.second)
            cout << t << endl;
}

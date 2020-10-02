#include <iostream>
#include <map>
#include <sstream>
#include <iterator>
using namespace std;

int main(){
    string line, word, translate;
    map<string, string> dic;
    int count = 0;

    while (!cin.eof())
    {
        while(!cin.eof()){
            std::getline(cin, line);
            std::istringstream iss(line);
            count = std::distance(std::istream_iterator<string>(iss),  std::istream_iterator<string>());
            std::istringstream iss2(line);
            if(count == 2)
                while (iss2 >> word >> translate)
                    dic[translate] = word;
            else
                break;
        }
        while (!cin.eof())
        {
            if(cin >> word){
                auto t = dic.find(word);
                cout << (t != dic.end() ? t->second : "eh") << endl;
            }
        }
        return 0;
    }
}

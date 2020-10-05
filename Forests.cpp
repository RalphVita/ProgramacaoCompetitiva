#include <iostream>
#include <sstream>
#include <map>
#include <set>
using namespace std;

int main() {
    int casos;
    int P, T;
    int i, j;
    map<int,set<int>> map;
    set<set<int>> sets;
    string s;

    while (!cin.eof())
    {
        getline(cin, s);
        stringstream ss1(s);
        ss1 >> casos;
        //cin >> casos;
        getline(cin, s);
        while (casos > 0)
        {
            
            sets.clear();
            map.clear();
            
            getline(cin, s);
            stringstream ss2(s);
            ss2 >> P >> T;
            //cin >> P >> T;
            //getline(cin, s);
            
            
            for (int k = 1; k <= P; k++)
                map[k].insert(0);
            
            while (getline(cin, s) && (int)s[0] != 13){
                stringstream ss(s);
                ss >> i >> j;
                map[i].insert(j);
                //cout << i << " " << j<< endl;
            }

            for (auto m : map)
                sets.insert(m.second);

           /* for (auto m : sets) {
                for (auto m1 : m)
                    cout << m1 << " ";
                cout << endl;
            }*/


            cout << sets.size() << endl;
            --casos;
            if(casos > 0)
                cout << endl;
        }

    }
}
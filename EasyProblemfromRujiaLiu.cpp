#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

int main() {
    int n, m;
    int k, v;
    int x;
    
    map<int, vector<int>> map;

    while (!cin.eof())
    {
        if (cin >> n >> m) {
            map.clear();
            for (int i = 0;i  < n; ++i){
                cin >> x;
                map[x].push_back(i+1);
            }

            for (;m > 0; --m) {
                cin >> k >> v;
                auto it = map.find(v);
                if (it != map.end())
                    cout << (it->second.size() >= k ? it->second[k-1] : 0) << endl;
                else
                    cout << 0 << endl;
            }
        }
    }
}
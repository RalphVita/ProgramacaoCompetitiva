#include <iostream>
#include <sstream>
#include <map>
#include <set>


#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;

class UnionFind {                                // OOP style
private:
    vi p, rank, setSize;                           // vi p is the key part
    int numSets;
public:
    UnionFind(int N) {
        p.assign(N, 0); for (int i = 0; i < N; ++i) p[i] = i;
        rank.assign(N, 0);                           // optional speedup
        setSize.assign(N, 1);                        // optional feature
        numSets = N;                                 // optional feature
    }

    int findSet(int i) { return (p[i] == i) ? i : (p[i] = findSet(p[i])); }
    bool isSameSet(int i, int j) { return findSet(i) == findSet(j); }

    int numDisjointSets() { return numSets; }      // optional
    int sizeOfSet(int i) { return setSize[findSet(i)]; } // optional

    void unionSet(int i, int j) {
        if (isSameSet(i, j)) return;                 // i and j are in same set
        int x = findSet(i), y = findSet(j);          // find both rep items
        if (rank[x] > rank[y]) swap(x, y);           // keep x 'shorter' than y
        p[x] = y;                                    // set x under y
        if (rank[x] == rank[y]) ++rank[y];           // optional speedup
        setSize[y] += setSize[x];                    // combine set sizes at y
        --numSets;                                   // a union reduces numSets
    }
};

int main() {
    int casos;
    int P, T;
    int i, j;
    map<int,set<int>> map;
    set<set<int>> sets;
    string s;

    while (!cin.eof())
    {
        cin >> casos;
       
        while (casos > 0)
        {
            sets.clear();
            map.clear();
            
            cin >> P >> T;
            getline(cin, s);

            UnionFind UF(P+T);

            /*for (int k = 1; k <= P; k++)
                UF.unionSet(k + T, 0);*/
                //map[i].insert(0);
            
            while (getline(cin, s) && (int)s[0] != 13){
                stringstream ss(s);
                ss >> i >> j;
                //map[i].insert(j);
                UF.unionSet(i + T - 1, j - 1);
            }

            /*for (auto m : map)
                sets.insert(m.second);*/

            //cout << sets.size() << endl;
            cout << UF.numDisjointSets() << endl;
            --casos;
            if(casos > 0)
                cout << endl;
        }

    }
}
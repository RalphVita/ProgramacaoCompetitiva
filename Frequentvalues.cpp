#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <iomanip>
#include <algorithm>
using namespace std;
#define DESLOQUE 100000

typedef vector<int> vi;

class SegmentTree {                              // OOP style
private:
  int n;                                         // n = (int)A.size()
  vi A, st, lazy;                                // the arrays

  int l(int p) { return  p<<1; }                 // go to left child
  int r(int p) { return (p<<1)+1; }              // go to right child

  int conquer(int a, int b) {
    if (a == -1) return b;                       // corner case
    if (b == -1) return a;
    return min(a, b);                            // RMQ
  }

  void build(int p, int L, int R) {              // O(n)
    if (L == R)
      st[p] = A[L];                              // base case
    else {
      int m = (L+R)/2;
      build(l(p), L  , m);
      build(r(p), m+1, R);
      st[p] = conquer(st[l(p)], st[r(p)]);
    }
  }

  void propagate(int p, int L, int R) {
    if (lazy[p] != -1) {                         // has a lazy flag
      st[p] = lazy[p];                           // [L..R] has same value
      if (L != R)                                // not a leaf
        lazy[l(p)] = lazy[r(p)] = lazy[p];       // propagate downwards
      else                                       // L == R, a single index
        A[L] = lazy[p];                          // time to update this
      lazy[p] = -1;                              // erase lazy flag
    }
  }

  int RMQ(int p, int L, int R, int i, int j) {   // O(log n)
    propagate(p, L, R);                          // lazy propagation
    if (i > j) return -1;                        // infeasible
    if ((L >= i) && (R <= j)) return st[p];      // found the segment
    int m = (L+R)/2;
    return conquer(RMQ(l(p), L  , m, i          , min(m, j)),
                   RMQ(r(p), m+1, R, max(i, m+1), j        ));
  }

  void update(int p, int L, int R, int i, int j, int val) { // O(log n)
    propagate(p, L, R);                          // lazy propagation
    if (i > j) return;
    if ((L >= i) && (R <= j)) {                  // found the segment
      lazy[p] = val;                             // update this
      propagate(p, L, R);                        // lazy propagation
    }
    else {
      int m = (L+R)/2;
      update(l(p), L  , m, i          , min(m, j), val);
      update(r(p), m+1, R, max(i, m+1), j        , val);
      int lsubtree = (lazy[l(p)] != -1) ? lazy[l(p)] : st[l(p)];
      int rsubtree = (lazy[r(p)] != -1) ? lazy[r(p)] : st[r(p)];
      st[p] = (lsubtree <= rsubtree) ? st[l(p)] : st[r(p)];
    }
  }

public:
  SegmentTree(int sz) : n(sz), st(4*n), lazy(4*n, -1) {}

  SegmentTree(const vi &initialA) : SegmentTree((int)initialA.size()) {
    A = initialA;
    build(1, 0, n-1);
  }

  void update(int i, int j, int val) { update(1, 0, n-1, i, j, val); }

  int RMQ(int i, int j) { return RMQ(1, 0, n-1, i, j); }
};



int main() {
    vi A;
    int n, g;
    int x;
    int i, j;

    //int v[2*DESLOQUE] = {};
    map<int, int> v;
    while (!cin.eof())
    {
        cin >> n;
        if(!n)
            return 0;

        cin >> g;

        A.clear();

       /* for (int i = 0; i < 2*DESLOQUE; i++)
          v[i] = 1;*/
        v.clear();
        
        for (int k = 0; k < n; ++k)
        {
            cin >> x;
            //if(x > 0)
              //v[x+ DESLOQUE]++;
            v[x]++;

            A.push_back(-v[x]);
        }

        //for (int i = 0; i < n; i++)
        /*for(auto m: v)
          A.push_back(-m.second);*/

        for (auto m : A)
            cout << m << endl;

        cout << "----------------" << endl;
        
        
        
        SegmentTree st(A);

        for (int k = 0; k < g; ++k)
        {
            cin >> i >> j;
            /*int h = st.RMQ(i-1, i-1);
            st.update(i-1, i-1, h - st.RMQ(i - 2, i - 2));

            for (auto m : A)
                cout << h << endl;
            cout << "----------------" << endl;*/

            cout << i <<  " " << j  << " -> "<< -st.RMQ(i-1,j-1) << endl;
            //st.update(i-1, i-1, h);
        }
    }


}
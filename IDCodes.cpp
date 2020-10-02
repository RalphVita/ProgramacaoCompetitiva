#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
    string str;
    while (true)
    {
        cin >> str;
        if(str == "#")
            return 0;
        if (next_permutation(str.begin(), str.end()))
            cout << str << endl;
        else
            cout << "No Successor" << endl;
    }
}
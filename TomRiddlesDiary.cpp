#include <iostream>
#include <set>
using namespace std;


int main() {
    int n;
    string name;
    set<string> names;
    int count = 0;

    while (!cin.eof())
    {
        cin >> n;
        while (n--) {
            cin >> name;
            count = names.size();
            names.insert(name);

            cout << (count == names.size() ? "YES" : "NO") << endl;
        }
        return 0;
    }
}
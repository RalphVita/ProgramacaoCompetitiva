#include <iostream>
using namespace std;

int main() {
    int t,n;
    string str;
    int count = 0;

    while (!cin.eof())
    {
        cin >> t;
        while (t--) {
            cin >> n;
            count = 0;
            
            cin >> str;
            for (auto p : str) 
                if (p == '(')
                    count++;
                else if (count > 0)
                    count--;

            cout << count << endl;
        }
        return 0;
    }
}
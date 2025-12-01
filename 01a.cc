#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int pos = 50;
    int out = 0;
    char c;
    int x;
    while (cin >> c >> x)
    {
        if (c == 'R') pos = (pos + x) % 100;
        else pos = (pos - x + 100) % 100;
        if (pos == 0) out++;
    }
    cout << out << endl;
}
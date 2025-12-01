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
        int prepos = pos;
        if (c == 'R') pos += x;
        else pos -= x;
        if (prepos == 0 and pos < 0) out--;
        while (pos < 0) 
        {
            out++;
            pos += 100;
        }
        if (pos == 0) out++;
        while (pos >= 100) 
        {
            out++;
            pos -= 100;
        }
        //cout << pos << "; " << out << endl;
    }
    cout << out << endl;
}
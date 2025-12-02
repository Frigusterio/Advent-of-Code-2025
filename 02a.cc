#include <iostream>
#include <vector>
#include <math.h>
#define int long long
using namespace std;

int digits(int n)
{
    int out = 0;
    while (n > 0)
    {
        n /= 10;
        out++;
    }
    return out;
}

bool invalid(int x)
{
    int d = digits(x);
    if (d % 2 != 0) return false;
    for (int i = 0; i < d/2; i++)
    {
        if (x / (int)pow(10,i) % 10 != x / (int)pow(10,i+d/2) % 10) return false;
    }
    return true;
}

signed main()
{
    int out = 0;
    int l, r;
    char x;
    while(cin >> l >> x >> r)
    {
        for (int i = l; i <= r; i++)
        {
            if (invalid(i)) out += i;
        }
        if (!(cin >> x)) break;
    }
    cout << out << endl;
}
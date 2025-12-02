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
    for (int div = 2; div <= d; div++)
    {
        if (d % div != 0) continue;
        int xcopy = x;
        int chunkSize = (int)pow(10, d / div);
        int chunk = x % chunkSize;
        xcopy /= chunkSize;
        bool valid = false;
        while (!valid and xcopy > 0)
        {
            if (xcopy % chunkSize != chunk) valid = true;
            xcopy /= chunkSize;
        }
        if (!valid) return true;    
    }
    return false;
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
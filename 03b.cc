#include <iostream>
#include <vector>
#define int long long
using namespace std;

signed main()
{
    int out = 0;
    string s;
    while (cin >> s)
    {
        const int m = 12;
        int n = s.size();
        int max, maxi = -1;
        int joltage = 0;
        for (int t = 0; t < m; t++)
        {
            max = s[maxi+1] - '0';
            maxi++;
            for (int i = maxi+1; i < n-m+1+t; i++)
            {
                if (max < s[i] - '0')
                {
                    max = s[i] - '0';
                    maxi = i;
                }
            }
            joltage = 10*joltage + max;
        }
        out += joltage;
    }
    cout << out << endl;
}
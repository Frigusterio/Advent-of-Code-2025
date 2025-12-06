#include <iostream>
#include <vector>
#include <fstream>
#define int long long
using namespace std;

signed main()
{
    const int t = 4;
    vector<int> v[t];

    for (int i = 0; i < t; i++)
    {
        while(cin.peek() != '\n')
        {
            int x;
            cin >> x;
            v[i].push_back(x);
            while(cin.peek() != '\n' and !('0' <= cin.peek() and cin.peek() <= '9')) cin.get();
        }
        cin.get();
    }
    
    int n = v[0].size();
    int out = 0;

    for (int i = 0; i < n; i++)
    {
        char c;
        cin >> c;
        if (c == '*') out += v[0][i] * v[1][i] * v[2][i] * v[3][i];
        else out += v[0][i] + v[1][i] + v[2][i] + v[3][i];
    }
    cout << out << endl;
}
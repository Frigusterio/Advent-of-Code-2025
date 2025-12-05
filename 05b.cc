#include <iostream>
#include <vector>
#include <set>
#include <fstream>
#define int long long
using namespace std;

signed main()
{
    ifstream file("05.input");
    string s;
    set<pair<int, int>> ranges;

    while (getline(file, s))
    {
        if (s == "") break;
        else
        {
            int i = 0;
            while (s[i]!='-') i++;
            string r1 = s.substr(0,i);
            string r2 = s.substr(i+1);
            ranges.insert({stoll(r1),stoll(r2)});
        }
    }
    int fresh = 0;
    int last_fresh_spot = 0;
    for (auto r : ranges)
    {
        fresh += r.second - r.first + 1;
        if (last_fresh_spot >= r.first) fresh -= (min(last_fresh_spot, r.second) - r.first + 1);
        last_fresh_spot = max(last_fresh_spot, r.second);
    }
    cout << fresh << endl;
}
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
    bool reading_ranges = true;
    int fresh = 0;
    while (getline(file, s))
    {
        if (reading_ranges)
        {
            if (s == "") reading_ranges = false;
            else
            {
                int i = 0;
                while (s[i]!='-') i++;
                string r1 = s.substr(0,i);
                string r2 = s.substr(i+1);
                ranges.insert({stoll(r1),stoll(r2)});
            }
            continue;
        }

        bool is_fresh = false;
        int n = stoll(s);
        for (auto a : ranges)
        {
            if (a.first <= n and n <= a.second)
            {
                is_fresh = true;
                break;
            }
        }
        fresh += is_fresh;
    }
    cout << fresh << endl;
}
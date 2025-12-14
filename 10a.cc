#include <iostream>
#include <vector>
#include <queue>
using namespace std;

signed main()
{
    // Input: [.#.#.] (a,b,c) (d,e,f) {g,h,i}
    int out = 0;
    char c;
    while (cin >> c)
    {
        int lights = 0, i = 0;
        cin >> c;
        while (c != ']')
        {
            if (c == '#') lights |= 1 << i;
            i++;
            cin >> c;
        }
        vector<int> v;
        while (c != '{')
        {
            cin >> c;
            switch (c)
            {
            case '(':
                v.push_back(0);
            case ',':
            case ')':
            case '{':
                break;
            default:
                v[v.size()-1] |= 1 << (c-'0');
            }
        }
        vector<int> jolts;
        while (c != '}')
        {
            jolts.push_back(0);
            cin >> jolts[jolts.size()-1] >> c;
        }
        /*
        cout << lights << endl;
        for (int x : v) cout << x << ' ';
        cout << endl;
        for (int x : jolts) cout << x << ' ';
        cout << endl;
        //*/
        int found = -1;
        if (lights == 0) found = 0;
        queue<vector<int>> q; // (numcount,num,lasti)
        for (int i = 0; i < v.size(); i++) q.push({1,v[i],i});
        while (!q.empty() and found == -1)
        {
            int numcount = q.front()[0];
            int num = q.front()[1];
            int lasti = q.front()[2];
            q.pop();
            
            if (num == lights)
            {
                found = numcount;
                break;
            }
            for (int j = lasti+1; j < v.size(); j++)
            {
                q.push({numcount+1,num xor v[j],j});
            }
            
        }
        out += found;
    }
    cout << out << endl;
}
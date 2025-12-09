#include <iostream>
#include <vector>
#define int long long
#define pint pair<int, int>
#define x first
#define y second
using namespace std;

signed main()
{
    int x,y;
    vector<pint> v;
    char c;
    while (cin >> x >> c >> y) v.push_back({x,y});
    int maxarea = 0;
    int n = v.size();
    for (int i = 0; i < n-1; i++) for (int j = i+1; j < n; j++)
    {
        maxarea = max(maxarea, (abs(v[i].x-v[j].x)+1)*(abs(v[i].y-v[j].y)+1));
    }
    cout << maxarea << endl;
    
}
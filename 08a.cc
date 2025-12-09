#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
#define int long long
using namespace std;
typedef pair<double, pair<int,int>> node;

struct pos{
    int x,y,z;
};

double distance(pos a, pos b)
{
    return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y) + (a.z-b.z)*(a.z-b.z));
}

void dfs(int i, const vector<vector<int>>& g, vector<bool>& visited, vector<int>& circuits)
{
    visited[i] = true;
    circuits[circuits.size()-1]++;
    for (int j : g[i]) if (!visited[j]) dfs(j,g,visited,circuits);
}

signed main()
{
    vector<pos> boxes;
    int x,y,z;
    char c;
    while (cin >> x >> c >> y >> c >> z) boxes.push_back({x,y,z});
    int n = boxes.size();
    vector<vector<int>> g(n);
    vector<node> q;
    for (int i = 0; i < n-1; i++) for (int j = i+1; j < n; j++)
    {
        q.push_back({distance(boxes[i],boxes[j]), {i,j}});
    }
    sort(q.begin(), q.end());
    for (int t = 0; t < 1000; t++)
    {
        g[q[t].second.first].push_back(q[t].second.second);
        g[q[t].second.second].push_back(q[t].second.first);
    }
    vector<int> circuits;
    vector<bool> visited(n,false);
    for (int i = 0; i < n; i++)
    {
        if (!visited[i])
        {
            circuits.push_back(0);
            dfs(i, g, visited, circuits);
        }
    }
    sort(circuits.begin(), circuits.end());
    cout << circuits[circuits.size()-1] * circuits[circuits.size()-2] * circuits[circuits.size()-3] << endl;
}
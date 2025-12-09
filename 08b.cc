#include <iostream>
#include <vector>
#include <math.h>
#include <queue>
#include <algorithm>
#define int long long
using namespace std;
typedef pair<double, pair<int,int>> edge;

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
    vector<edge> edges;
    vector<bool> visited(n,false);
    priority_queue<edge, vector<edge>, greater<edge>> q;
    for (int j = 1; j < n; j++)
    {
        q.push({distance(boxes[0],boxes[j]),{0,j}});
    }
    visited[0] = true;
    while(!q.empty())
    {
        edge e = q.top();
        int i = e.second.second;
        q.pop();
        if (visited[i]) continue;
        visited[i] = true;
        edges.push_back(e);
        for (int j = 0; j < n; j++)
        {
            if (!visited[j])
            {
                q.push({distance(boxes[i],boxes[j]),{i,j}});
            }
        }
    }
    sort(edges.begin(), edges.end());
    edge last = edges[edges.size()-1];
    cout << boxes[last.second.first].x * boxes[last.second.second].x << endl;
}
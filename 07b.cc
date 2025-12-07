#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#define int long long
#define pint pair<int, int>
#define x first
#define y second
using namespace std;

signed main(signed argc, char *argv[])
{
    ifstream file(argc >= 2 ? argv[1] : "07.input");
    string s;
    queue<pint> q;
    vector<string> M;
    while (getline(file, s))
    {
        M.push_back(s);
    }
    int n = M.size(), m = M[0].size();
    vector<vector<int>> timelines (n, vector<int>(m,0));
    for (int j = 0; j < m; j++)
    {
        if (M[0][j] == 'S') 
        {
            q.push({0,j});
            timelines[0][j] = 1;
            break;
        }
    }
    while (!q.empty())
    {
        pint p = q.front();
        q.pop();
        pint newp = {p.x + 1, p.y};
        if (newp.x >= n) continue;
        if (M[newp.x][newp.y] != '^')
        {
            timelines[newp.x][newp.y] += timelines[p.x][p.y];
            if (M[newp.x][newp.y] == '.')
            {
                M[newp.x][newp.y] = '|';
                q.push(newp);
            }
        }
        else
        {
            if (newp.y - 1 >= 0)
            {
                timelines[newp.x][newp.y-1] += timelines[p.x][p.y];
                if (M[newp.x][newp.y-1] == '.')
                {
                    M[newp.x][newp.y-1] = '|';
                    q.push({newp.x, newp.y-1});
                }
            }
            if (newp.y + 1 < m)
            {
                timelines[newp.x][newp.y+1] += timelines[p.x][p.y];
                if (M[newp.x][newp.y+1] == '.')
                {
                    M[newp.x][newp.y+1] = '|';
                    q.push({newp.x, newp.y+1});
                }
            }
        }
    }
    int out = 0;
    for (int x : timelines[n-1])
        out += x;
    cout << out << endl;
}
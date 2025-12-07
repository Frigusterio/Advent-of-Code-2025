#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#define pint pair<int, int>
#define x first
#define y second
using namespace std;

int main(int argc, char *argv[])
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
    for (int j = 0; j < m; j++)
    {
        if (M[0][j] == 'S') 
        {
            q.push({0,j});
            break;
        }
    }
    int out = 0;
    while (!q.empty())
    {
        pint p = q.front();
        q.pop();
        pint newp = {p.x + 1, p.y};
        if (newp.x >= n) continue;
        if (M[newp.x][newp.y] == '.')
        {
            M[newp.x][newp.y] = '|';
            q.push(newp);
        }
        else if (M[newp.x][newp.y] == '^')
        {
            out++;
            if (newp.y - 1 >= 0 and M[newp.x][newp.y-1] == '.')
            {
                M[newp.x][newp.y-1] = '|';
                q.push({newp.x, newp.y-1});
            }
            if (newp.y + 1 < m and M[newp.x][newp.y+1] == '.')
            {
                M[newp.x][newp.y+1] = '|';
                q.push({newp.x, newp.y+1});
            }
        }
    }
    cout << out << endl;
}
#include <iostream>
#include <vector>
#define pint pair<int,int> 
using namespace std;

constexpr pint DIRS[8] = {{1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}, {0, -1}, {1, -1}};

int main()
{
    int out = 0;
    string s;
    vector<string> M;
    while (cin >> s) M.push_back(s);
    int n = M.size(), m = M[0].size();
    while (true)
    {
        vector<string> Mcopy(M);
        int removedThisIt = 0;
        for (int i = 0; i < n; i++) for (int j = 0; j < m; j++)
        {
            if (M[i][j] == '.') continue;
            int surrounding = 0;
            for (pint p : DIRS)
            {
                pint newpos = {i + p.first, j + p.second};
                if (0 <= newpos.first and newpos.first < n and 0 <= newpos.second and newpos.second < m and M[newpos.first][newpos.second] == '@')
                    surrounding++;
            }
            if (surrounding < 4)
            {
                removedThisIt++;
                Mcopy[i][j] = '.';
            }
        }
        if (removedThisIt > 0) out += removedThisIt;
        else break;

        M = Mcopy;
    }
    cout << out << endl;
    
}
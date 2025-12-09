#include <iostream>
#include <vector>
#include <map>
#include <set>
using namespace std;
#define int long long
#define pint pair<int, int>
#define x first
#define y second
constexpr pint DIRS[4] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

bool checker(const vector<pint>& v, map<pint,int>& M)
{
    int n = v.size();
    for (int i = 0; i < n; i++)
    {
        pint pprev = v[(i+n-1)%n], pi = v[i], pj = v[(i+1)%n];
        M[{pi.x,pi.y}] = 2;

        for (pint dir : DIRS)
        {
            pint pn = {pi.x + dir.x, pi.y + dir.y};
            if (M.count({pn.x,pn.y}) and M[{pn.x,pn.y}] == 2 and pn != pprev) return false;
        }

        if (pi.x == pj.x)
        {
            for (int y = min(pi.y,pj.y)+1; y < max(pi.y,pj.y); y++)
            {
                M[{pi.x,y}] = 1;
                if (M.count({pi.x-1,y}) or M.count({pi.x+1,y})) return false;
            }
        }
        else
        {
            for (int x = min(pi.x,pj.x)+1; x < max(pi.x,pj.x); x++)
            {
                M[{x,pi.y}] = 1;
                if (M.count({x,pi.y-1}) or M.count({x,pi.y+1})) return false;
            }
        }
    }

    /*
    const int size = 1000;
    vector<vector<char>> yea(size,vector<char>(size,'.'));
    int i = 0;
    for (auto m : M)
    {  
        if (m.second == 2)
        {
            yea[m.first.x / (100000/size)][m.first.y / (100000/size)] = i%10 + '0';
            i++;
        }
        else if (yea[m.first.x / (100000/size)][m.first.y / (100000/size)] == '.')
            yea[m.first.x / (100000/size)][m.first.y / (100000/size)] = '#'; 
    }

    for (int i = 0; i < size; i++) 
    {
        for (int j = 0; j < size; j++)
        {
            cout << yea[i][j];
        }
        cout << endl;
    }
    //*/

    return true;
}

void proceedWithBigBoy(pint bigboy, map<pint,int>& M, bool up)
{
    pint pos = bigboy;
    int direction = up ? 1 : -1;
    do {pos.y += direction;} while (!M.count(pos));
    while (M.count(pos)) pos.x--;
    while (!M.count(pos)) pos.x--;
    
    set<pair<int,pint>> maxareas;
    while(direction*pos.y > direction*bigboy.y)
    {
        while (M.count(pos) and M[pos] == 1) pos.y -= direction;
        maxareas.insert({(1+abs(pos.x-bigboy.x))*(1+abs(pos.y-bigboy.y)), pos});
        if (direction*pos.y <= direction*bigboy.y) break;
        if (M.count({pos.x-1,pos.y})) // Tetris S
        {
            do {pos.x--;} while(M.count(pos) and M[pos] == 1);
            maxareas.insert({(1+abs(pos.x-bigboy.x))*(1+abs(pos.y-bigboy.y)), pos});
        }
        else // ^
        {
            do {pos.x++;} while(M.count(pos) and M[pos] == 1);
            auto it = maxareas.begin();
            while (it != maxareas.end())
            {
                if (it->second.x < pos.x) it = maxareas.erase(it);
                else it++;
            }
            maxareas.insert({(1+abs(pos.x-bigboy.x))*(1+abs(pos.y-bigboy.y)), pos});
        }
        pos.y -= direction;
    }

    for (auto x : maxareas) cout << x.first << ": " << x.second.x << ", " << x.second.y << "; ";
    cout << endl;
}

signed main()
{
    int x,y;
    vector<pint> v;
    char c;
    while (cin >> x >> c >> y) v.push_back({x,y});
    int n = v.size();

    map<pint,int> M;
    checker(v, M);

    v.push_back(v[0]);
    v.push_back(v[1]);

    int total_clockwise_angle = 0;
    for (int i = 0; i < n; i++)
    {
        pint e1 = {v[i+1].x-v[i].x, v[i+1].y-v[i].y};
        pint e2 = {v[i+2].x-v[i+1].x, v[i+2].y-v[i+1].y};
        int dir1 = e1.x == 0 ? (e1.y > 0 ? 0 : 2) : (e1.x > 0 ? 1 : 3);
        int dir2 = e2.x == 0 ? (e2.y > 0 ? 0 : 2) : (e2.x > 0 ? 1 : 3);
        total_clockwise_angle += (dir2 - dir1 + 6) % 4 - 2;

       // if (v[i].x < 4200 and v[i].y > 49400) cout << total_clockwise_angle << ' ';
    }
    //cout << endl;

    pint bigboy1 = {94891,50375};
    pint bigboy2 = {94891,48378};
    proceedWithBigBoy(bigboy1, M, true);
    proceedWithBigBoy(bigboy2, M, false);
}
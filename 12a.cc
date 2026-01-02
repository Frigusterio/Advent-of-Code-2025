#include <iostream>
#include <vector>
#include <bitset>
#include <set>
using namespace std;
constexpr pair<int,int> DIRS[4] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
typedef vector<vector<bool>> Piece;

constexpr int PCOUNT = 6;
constexpr int PSIZE = 3;

int funnyCounter = 0;
const int LIMIT = 1000;

template <typename T> void print_vector(const vector<T>& v)
{
    for (int i = 0; i < v.size(); i++)
    {
        cout << v[i] << ' ';
    }
    cout << endl;
}

template <typename T> void print_matrix(const vector<vector<T>>& M)
{
    for (int i = 0; i < M.size(); i++)
    {
        for (int j = 0; j < M[i].size(); j++)
        {
            cout << (M[i][j] ? '#' : ' ');
        }
        cout << endl;
    }
}

Piece rotatedClockwise(const Piece& p)
{
    Piece piece(PSIZE, vector<bool>(PSIZE));
    for (int i = 0; i < PSIZE; i++) for (int j = 0; j < PSIZE; j++)
    {
        piece[i][j] = p[j][PSIZE-1-i];
    }
    return piece;
}

Piece rotatedCounterclockwise(const Piece& p)
{
    Piece piece(PSIZE, vector<bool>(PSIZE));
    for (int i = 0; i < PSIZE; i++) for (int j = 0; j < PSIZE; j++)
    {
        piece[i][j] = p[PSIZE-1-j][i];
    }
    return piece;
}

void rotateClockwise(Piece& piece)
{
    Piece p(piece);
    for (int i = 0; i < PSIZE; i++) for (int j = 0; j < PSIZE; j++)
    {
        piece[i][j] = p[j][PSIZE-1-i];
    }
}

void rotateCounterclockwise(Piece& piece)
{
    Piece p(piece);
    for (int i = 0; i < PSIZE; i++) for (int j = 0; j < PSIZE; j++)
    {
        piece[i][j] = p[PSIZE-1-j][i];
    }
}

Piece flippedRows(Piece piece)
{
    for (int i = 0; i < PSIZE; i++) for (int j = 0; j < PSIZE / 2; j++)
    {
        swap(piece[i][j], piece[i][PSIZE-1-j]);
    }
    return piece;
}

void flipRows(Piece& piece)
{
    for (int i = 0; i < PSIZE; i++) for (int j = 0; j < PSIZE / 2; j++)
    {
        swap(piece[i][j], piece[i][PSIZE-1-j]);
    }
}

bool uniqueFlip(const Piece& piece)
{
    Piece flipped = flippedRows(piece);
    for (int i = 0; i < 4; i++)
    {
        if (piece == flipped) return false;
        flipped = rotatedClockwise(flipped);
    }
    return true;    
}

// Returns whether a piece with its top-left corner on pos would fit
bool fitsTopLeftCorner(const Piece& piece, const pair<int,int>& pos, const vector<vector<bool>>& region)
{
    int n = region.size(), m = region[0].size();
    for (int i = 0; i < PSIZE; i++) for (int j = 0; j < PSIZE; j++)
    {
        int newi = pos.first + i;
        int newj = pos.second + j;
        if (newi < 0 or newi >= n or newj < 0 or newj >= m or (piece[i][j] and region[newi][newj]))
        {
            return false;
        }
    }
    return true;
}

void updateCandidates(int i0, int i1, int j0, int j1, vector<vector<bool>>& region, set<pair<int,int>>& candidateSquares)
{
    int n = region.size(), m = region[0].size();
    for (int i = i0; i <= i1; i++) for (int j = j0; j <= j1; j++) 
    {
        bool nearPiece = i == 0;
        if (!nearPiece) for (auto dir : DIRS)
        {
            pair<int,int> newpos = {i + dir.first, j + dir.second};
            if (newpos.first < 0 or newpos.first >= n or newpos.second < 0 or newpos.second >= m) continue;
            if (region[newpos.first][newpos.second])
            {
                nearPiece = true;
                break;
            }
        }
        if (nearPiece) candidateSquares.insert({i,j});
        else candidateSquares.erase({i,j});
    } 
}

void placePiece(const vector<Piece>& pieces, int p, int r, pair<int,int> pos, vector<int>& pcounts, vector<vector<bool>>& region, /*set<vector<int>>& situation,*/ set<pair<int,int>>& candidateSquares)
{
    pcounts[p]--;
    //situation.insert({pos.first, pos.second, p, r});
    for (int i = 0; i < PSIZE; i++) for (int j = 0; j < PSIZE; j++)
    {
        if (pieces[p][i][j]) region[pos.first + i][pos.second + j] = true;
    }
    updateCandidates(pos.first - 1, pos.first + PSIZE, pos.second - 1, pos.second + PSIZE, region, candidateSquares);
}

void removePiece(const vector<Piece>& pieces, int p, int r, pair<int,int> pos, vector<int>& pcounts, vector<vector<bool>>& region, /*set<vector<int>>& situation,*/ set<pair<int,int>>& candidateSquares)
{
    pcounts[p]++;
    //situation.erase({pos.first, pos.second, p, r});
    for (int i = 0; i < PSIZE; i++) for (int j = 0; j < PSIZE; j++)
    {
        if (pieces[p][i][j]) region[pos.first + i][pos.second + j] = false;
    }
    updateCandidates(pos.first - 1, pos.first + PSIZE, pos.second - 1, pos.second + PSIZE, region, candidateSquares);
}

bool possibleConfig(vector<Piece>& pieces, vector<int>& pcounts, vector<vector<bool>>& region, /*set<vector<int>>& situation,*/ set<pair<int,int>>& candidateSquares, set</*set<vector<int>>*/vector<vector<bool>>>& cache)
{
    /*
    print_vector(pcounts);
    print_matrix(region);
    cout << endl;//*/
    funnyCounter++;
    if (funnyCounter >= LIMIT) return false;
    if (funnyCounter % 10000 == 0)
    {
        cout << '.';
        if (funnyCounter == 100000)
        {
            cout << cache.size();
            funnyCounter = 0;
        }
        cout.flush();
    }

    bool weDidItBoys = true;
    for (int x : pcounts) if (x > 0) weDidItBoys = false;
    if (weDidItBoys) return true;

    if (cache.count(region)) return false;

    for (auto pos : candidateSquares) for (int p = 0; p < PCOUNT; p++) 
    {   
        if (pcounts[p] == 0) continue;
        Piece& piece = pieces[p];
        bool hasUniqueFlip = uniqueFlip(piece);
        for (int r = 0; r < 4; r++)
        {
            for (int i = 0; i < PSIZE; i++) for (int j = 0; j < PSIZE; j++)
            {
                if (funnyCounter >= LIMIT) return false;

                pair<int,int> newpos = {pos.first - i, pos.second - j};
                if (fitsTopLeftCorner(piece, newpos, region))
                {
                    placePiece(pieces, p, r, newpos, pcounts, region, /*situation,*/ candidateSquares);
                    if (possibleConfig(pieces, pcounts, region, /*situation,*/ candidateSquares, cache)) return true;
                    removePiece(pieces, p, r, newpos, pcounts, region, /*situation,*/ candidateSquares);
                }
                if (hasUniqueFlip)
                {
                    flipRows(piece);
                    if (fitsTopLeftCorner(piece, newpos, region))
                    {
                        placePiece(pieces, p, r+4, newpos, pcounts, region, /*situation,*/ candidateSquares);
                        if (possibleConfig(pieces, pcounts, region, /*situation,*/ candidateSquares, cache)) return true;
                        removePiece(pieces, p, r+4, newpos, pcounts, region, /*situation,*/ candidateSquares);
                    }
                    flipRows(piece);
                }
            }
            rotateClockwise(piece);
        }
    }

    cache.insert(region);
    return false;
}

signed main()
{
    vector<Piece> pieces(PCOUNT, Piece(PSIZE, vector<bool> (PSIZE, false)));
    char x;
    for (int p = 0; p < PCOUNT; p++)
    {
        cin >> x >> x;
        for (int i = 0; i < PSIZE; i++) for (int j = 0; j < PSIZE; j++)
        {
            cin >> x;
            if (x == '#') pieces[p][i][j] = true;
        }
    }

    int out = 0;
    int n, m;
    while (cin >> n >> x >> m >> x)
    {
        funnyCounter = 0;

        vector<int> pcounts(PCOUNT);
        for (int p = 0; p < PCOUNT; p++) cin >> pcounts[p];

        vector<vector<bool>> region (n, vector<bool>(m, false));
        //set<vector<int>> situation;
        //set<set<vector<int>>> cache;
        set<vector<vector<bool>>> cache;
        set<pair<int, int>> candidateSquares;
        for (int i = 0; i < n; i++)
        {
            candidateSquares.insert({i,0});
        }
        bool possible = possibleConfig(pieces, pcounts, region, candidateSquares, cache);
        out += possible;
        cout << "Finished one! Got " << (possible ? "true" : "false") << " in " << funnyCounter << endl;
    }
    cout << out << endl;
    // 481 potser?
}
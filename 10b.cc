#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <iomanip>
#include <math.h>
#define eps 1e-8
using namespace std;

template <typename T> struct node
{
    int numcount;
    vector<T> presses;
    int lastf;
};

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
    cout << fixed << setfill(' ') << setprecision(2);
    for (int i = 0; i < M.size(); i++)
    {
        for (int j = 0; j < M[i].size(); j++)
        {
            cout << setw(6) << M[i][j] << ' ';
        }
        cout << endl;
    }
}

bool cmp(vector<double> a, vector<double> b)
{
    for (int i = 0; i < a.size(); i++)
    {
        if (abs(a[i]) > abs(b[i])) return true;
        else if (abs(a[i]) < abs(b[i])) return false;
    }
    return true;
}

template<typename T> vector<T> operator+(vector<T> a, const vector<T>& b)
{
    for (int i = 0; i < a.size(); i++) a[i] += b[i];
    return a;
}

template<typename T> vector<T> operator-(vector<T> a, const vector<T>& b)
{
    for (int i = 0; i < a.size(); i++) a[i] -= b[i];
    return a;
}

template<typename T> vector<T> operator*(vector<T> b, T a)
{
    for (T& x : b) x*=a;
    return b;
}

template<typename T> vector<T> operator*(T a, vector<T> b)
{
    for (T& x : b) x*=a;
    return b;
}

template<typename T> vector<T> operator/(vector<T> b, T a)
{
    for (T& x : b) x/=a;
    return b;
}

template <typename T> vector<T> get_column(const vector<vector<T>>& M, int j)
{
    vector<T> v(M.size());
    for (int i = 0; i < M.size(); i++) v[i] = M[i][j];
    return v;
}

template <typename T> T sum_vector(const vector<T>& v)
{
    T sum = 0;
    for (T x : v) sum += x;
    return sum;
}

template<typename T> bool operator>=(const vector<T>& a, T b)
{
    for (T x : a) if (x < b-eps) return false;
    return true;
}

bool is_zeros(const vector<double>& v)
{
    for (double d : v) if (abs(d) > eps) return false;
    return true;
}

bool is_ints(const vector<double>& v)
{
    for (double d : v) if (abs(d - round(d)) > eps) return false;
    return true;
}

bool check(const vector<double>& presses, const vector<int>& v, const vector<int>& goalJolts, const vector<int>& freed)
{
    vector<int> jolts(goalJolts.size(),0);
    vector<int> reorderedPresses;
    int i = 0, f = 0;
    while (i+f < v.size())
    {
        if (freed.size() > 0 and freed[f] == i+f)
        {
            reorderedPresses.push_back(round(presses[v.size()-freed.size()+f]));
            f++;
        }
        else 
        {
            reorderedPresses.push_back(round(presses[i]));
            i++;
        }
    }
    //print_vector(reorderedPresses);
    
    for (int p = 0; p < v.size(); p++) for (int i = 0; i < goalJolts.size(); i++)
    {
        if ((v[p] >> i) & 1) jolts[i] += reorderedPresses[p];
    }

    if (jolts != goalJolts)
    {
        print_vector(jolts);
        print_vector(goalJolts);
    }

    return jolts == goalJolts;
}

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
            int x;
            cin >> x >> c;
            jolts.push_back(x);
        }
        int n = max(jolts.size(), v.size());
        int m = v.size();
        //cout << n << ", " << m << endl;
        vector<vector<double>> M(n, vector<double>(m+1, 0));
        for (int i = 0; i < n; i++) for (int j = 0; j <= m; j++)
        {
            if (j < m) M[i][j] = (v[j] >> i) & 1;
            else if (i < jolts.size()) M[i][j] = jolts[i];
        }

        int ig = 0;
        for (int j = 0; j < v.size(); j++)
        {
            sort(M.begin(), M.end(), cmp);
            /*
            print_matrix(M);
            cout << endl;//*/

            if (abs(M[ig][j]) <= eps) continue;

            M[ig] = M[ig]/M[ig][j];
            for (int i = 0; i < n; i++) if (i != ig)
            {
                M[i] = M[i] - M[ig]*M[i][j];
            }
            
            ig++;
        }
        //print_matrix(M);
        int freedom = 0;
        while (is_zeros(M[m-1-freedom])) freedom++;
        //cout << freedom << endl;
        ig = 0;
        int usedfreedom = 0;
        vector<int> freed (freedom);
        for (int j = 0; j < m; j++)
        {
            if (abs(M[ig][j]) <= eps)
            {
                freed[usedfreedom] = j;
                usedfreedom++;
            }
            else ig++;
        }
        //print_matrix(M);
        //cout << usedfreedom << endl;
        
        vector<double> presses = get_column(M, m);
        //for (int x : presses) cout << x << ' ';
        //cout << endl;

        /*
        cout << "freed: ";
        for (int f : freed) cout << f << ' ';
        cout << endl;//*/

        vector<int> maxPresses(freedom,__INT_MAX__), freePresses(freedom,0);
        for (int f = 0; f < freedom; f++) for (int i = 0; i < jolts.size(); i++) 
        {
            //cout << v[freed[f]] << endl;
            if ((v[freed[f]] >> i) & 1)
            {
                maxPresses[f] = min(maxPresses[f], jolts[i]);
            }
        }
        
        vector<double> bestPresses = presses;
        int bestSum = __INT_MAX__;
        if (freedom > 0) while (freePresses[freedom-1] <= maxPresses[freedom-1])
        {
            vector<double> newPresses = presses;
            for (int f = 0; f < freedom; f++)
            {
                newPresses = newPresses - (double)freePresses[f] * get_column(M, freed[f]);
                newPresses[m-freedom+f] += (double)freePresses[f];
            }

            if (newPresses >= -0.0 and is_ints(newPresses) and bestSum > round(sum_vector(newPresses)))
            {
                bestSum = round(sum_vector(newPresses));
                bestPresses = newPresses;
            }
            freePresses[0]++;
            for (int f = 1; f < freedom; f++) if (freePresses[f-1] > maxPresses[f-1])
            {
                freePresses[f-1] = 0;
                freePresses[f]++;
            }
        }
        else bestSum = round(sum_vector(bestPresses));

        if (!check(bestPresses, v, jolts, freed))
        {
            cout << "fuck!" << endl;
            print_vector(freed);
            print_vector(bestPresses);
            exit(1);
        }

        print_matrix(M);
        print_vector(bestPresses);
        cout << bestSum << endl;
        out += bestSum;
    }
    cout << out << endl;
}
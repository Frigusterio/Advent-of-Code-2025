#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int out = 0;
    string s;
    while (cin >> s)
    {
        int n = s.size();
        int max1 = s[0] - '0';
        int max1i = 0;
        for (int i = 1; i < n-1; i++)
        {
            if (max1 < s[i] - '0')
            {
                max1 = s[i] - '0';
                max1i = i;
            }
        }
        int max2 = s[max1i+1] - '0';
        int max2i = max1i+1;
        for (int i = max2i+1; i < n; i++)
        {
            if (max2 < s[i] - '0')
            {
                max2 = s[i] - '0';
                max2i = i;
            }
        }
        out += max1*10 + max2;        
    }
    cout << out << endl;
}
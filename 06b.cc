#include <iostream>
#include <vector>
#include <fstream>
#define int long long
using namespace std;

signed main(signed argc, char *argv[])
{
    if (argc != 2) exit(1);
    ifstream file(argv[1]);
    string s;
    vector<string> M;
    while (getline(file, s))
    {
        M.push_back(s);
    }
    string ops = M[M.size() - 1];
    M.pop_back();
    int n = M.size();

    int opsi = 0;

    int out = 0;
    while (opsi < ops.size())
    {
        int startopsi = opsi;
        int numbers = 0;
        do{
            opsi++;
            numbers++;
        }while(opsi < ops.size() and ops[opsi] == ' ');
        if (opsi < ops.size()) numbers--;

        int result = ops[startopsi] == '*';
        for (int i = 0; i < numbers; i++)
        {
            int number = 0;
            for (int j = 0; j < n; j++)
            {
                char c = M[j][startopsi + i];
                if(c != ' ') number = 10*number + c - '0';
            }

            if (ops[startopsi] == '*') result *= number;
            else result += number;
        }
        out += result;
    }
    cout << out << endl;
}
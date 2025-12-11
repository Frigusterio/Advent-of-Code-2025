#include <iostream>
#include <vector>
#include <map>
#include <fstream>
using namespace std;

map<string,vector<string>> ins, outs;
map<string,int> plingles;

int get_plingle(const string& s)
{
    if (plingles.count(s)) return plingles[s];
    int plingle = 0;
    for (string in : ins[s]) plingle += get_plingle(in);
    plingles[s] = plingle;
    return plingle;
}

signed main(signed argc, char *argv[])
{
    ifstream file(argc >= 2 ? argv[1] : "11.input");
    string s;

    while (getline(file, s))
    {
        string in = s.substr(0,3);
        for (int i = 5; i < s.size(); i+=4)
        {
            string out = s.substr(i,3);
            ins[out].push_back(in);
            outs[in].push_back(out);
        }
    }
    plingles["you"] = 1;
    cout << get_plingle("out") << endl;
}
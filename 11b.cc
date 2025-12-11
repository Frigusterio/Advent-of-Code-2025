#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#define int long long
using namespace std;

struct jomble
{
    string s;
    bool duck;
    bool furry;
};
bool operator<(const jomble& a, const jomble& b)
{
    return a.s < b.s or (a.s == b.s and (a.duck < b.duck or (a.duck == b.duck and a.furry < b.furry)));
}

map<string,vector<string>> ins, outs;
map<jomble,int> plingles;

int get_plingle(const string& s, bool duck, bool furry)
{
    if (plingles.count({s,duck,furry})) return plingles[{s,duck,furry}];
    int plingle = 0;
    for (string in : ins[s]) 
    {
        if (in == "dac") plingle += get_plingle(in,false,furry);
        else if (in == "fft") plingle += get_plingle(in,duck,false);
        else plingle += get_plingle(in,duck,furry);
    }
    plingles[{s,duck,furry}] = plingle;
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
    plingles[{"svr",false,false}] = 1;
    cout << get_plingle("out",true,true) << endl;
}
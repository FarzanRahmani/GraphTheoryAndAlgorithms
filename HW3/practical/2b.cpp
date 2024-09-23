//  use gpt and geeks for geeks

#include <iostream>
#include <vector>
#include <map>
#pragma GCC optimize("Ofast,unroll-loops,fast-math")
#define saraa ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
#define intTuple pair<int, int>
#define pb push_back

using namespace std;
#define int long long

vector<intTuple> edg;

int load[2000000];
int lenght_l[2000000];
int final;
int final_Num;
map<int, int> num_edg[2000000];
vector<intTuple> final_Neighbor[2000000];

bool donee[2000000];
bool pole[2000000];

void SwapValue(int &a, int &b)
{
    int t = a;
    a = b;
    b = t;
}

int minm(int x, int y)
{
    return (x < y) ? x : y;
}

void trace_algo(int nowVer, int node_main, int temp)
{
    load[nowVer] = lenght_l[nowVer];
    bool a = true;
    donee[nowVer] = a;

    for (const auto &update_node : final_Neighbor[nowVer])
    {
        int edgeee = update_node.first;
        int edgeeetemp = update_node.second;
        long long vv = node_main;
        if (!donee[edgeee])
        {
            lenght_l[edgeee] = lenght_l[nowVer] + 1;
            trace_algo(edgeee, nowVer, edgeeetemp);
            load[nowVer] = minm(load[nowVer], load[edgeee]);
        }

        else if (edgeee != vv)
        {
            load[nowVer] = minm(load[nowVer], lenght_l[edgeee]);
        }
    }

    if ((nowVer > 1 || nowVer < 1) && load[nowVer] == lenght_l[nowVer])
    {
        pole[temp] = true;
    }
}

int32_t main()
{
    saraa;

    int ver_numss;
    int ver_edgeee;
    cin >> ver_numss >> ver_edgeee;
    int i = 0;

    while (i < ver_edgeee)
    {
        {
            int first_ver;
            int second_ver;

            cin >> first_ver >> second_ver;

            if (first_ver > second_ver)
                SwapValue(first_ver, second_ver);

            if (first_ver > second_ver || first_ver < second_ver)
            {

                if (!num_edg[first_ver][second_ver])
                {
                    final_Neighbor[first_ver].pb({second_ver, final_Num});
                    final_Neighbor[second_ver].pb({first_ver, final_Num});
                    edg.pb({first_ver, second_ver});
                    final_Num++;
                }
                num_edg[first_ver][second_ver]++;
            }
        }
        i++;
    }

    int a = 1, b = 0;

    trace_algo(a, b, b);

    for (int i = b; i < final_Num; i = i + 1)

    {
        int s = edg[i].second;
        int r = edg[i].first;
        if (pole[i] && num_edg[r][s] == a)
        {

            final = final + 1;
        }
    }

    cout << final;
}
#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <set>
#include <algorithm>

using namespace std;

int degree_cnt;
int point[10000];
vector<int> edge[10000];

void dfs(int idx)
{
    set<int> colors;
    for (int i = 0; i < edge[idx].size();i++){
        if (point[edge[idx][i]]){
            colors.insert(point[edge[idx][i]]);
        }
    }
    for (int i = 1; i <= degree_cnt; i++)
    {
        if (colors.count(i) == 0){
            point[idx] = i;
            break;
        }
    }

    for (int i = 0;i<edge[idx].size();i++){
        if (!point[edge[idx][i]]){
            dfs(edge[idx][i]);
        }
    }
}

int main()
{
    ifstream fin("input.txt");
    cin.rdbuf(fin.rdbuf());

    int n, m;
    int case_n = 0;
    while (cin >> n >> m)
    {
        if (case_n){
            cout << endl;
        }
        case_n ++;
        degree_cnt = -1;
        memset(point,0,sizeof(int)*n);
        for (int i = 0; i < n; i++)
        {
            edge[i].clear();
        }
        for (int i = 0;i<m;i++){
            int a, b;
            cin >> a >> b;
            a--;
            b--;
            edge[a].push_back(b);
            edge[b].push_back(a);
        }
        for (int i = 0;i<n;i++){
            degree_cnt = max(degree_cnt, (int)edge[i].size());
        }
        degree_cnt = (degree_cnt % 2) ? degree_cnt : degree_cnt + 1;
        dfs(0);
        cout << degree_cnt << endl;
        for (int i = 0; i < n; i++)
        {
            cout << point[i] << endl;
        }
    }
}

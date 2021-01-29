#include <iostream>
#include <fstream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;
const int MaxN=22;

vector<int> edge[MaxN];
int vis[MaxN];
int f[MaxN];
int fire_num;
int ans_num;
void print(int num){
    if (f[num]==-1){
       printf("%d",num);
       return;
    }
    else{
        print(f[num]);
        printf(" %d",num);
    }
}
bool dfs_judge(int now){
    if (now==fire_num){
        return true;
    }
    for (int i =0;i<edge[now].size();i++){
        int next=edge[now][i];
        if (!vis[next]){
            vis[next]=1;
            if (dfs_judge(next)){
                return true;
            }
        }
    }
    return false;
}
void dfs(set<int>& table,int now){
    if (now==fire_num){
        ans_num++;
        print(now);
        printf("\n");
        return;
    }
    for (int i =0;i<edge[now].size();i++){
        int next = edge[now][i];
        if (table.count(next) ==0){
            f[next]=now; 
            table.insert(next);
            dfs(table,next);
            table.erase(next);
        }
    }
}

int main()
{
    ifstream fin("input.txt");
    cin.rdbuf(fin.rdbuf());
    int case_num=0;
    while (cin >> fire_num){
        case_num++;
        memset(f,-1,sizeof(f));
        memset(vis,0,sizeof(vis));
        ans_num = 0;
        for (int i =0;i<MaxN;i++){
            edge[i].clear();
        }
        int a,b;
        while (cin >> a >> b && a!=0 && b!=0){
            edge[a].push_back(b);
            edge[b].push_back(a);
        }
        for (int i =0;i<MaxN;i++){
            sort(edge[i].begin(),edge[i].end());
        }
        set<int> table;
        table.insert(1);
        printf("CASE %d:\n",case_num);
        if (dfs_judge(1)){
            dfs(table,1);
        }
        printf("There are %d routes from the firestation to streetcorner %d.\n",ans_num,fire_num);
    }
}
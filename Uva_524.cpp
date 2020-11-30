#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

const int MaxN = 40;

int isp[MaxN];
int ans[MaxN];
int vis[MaxN];

void search(int n,int cur){
    if (cur==n){
        if (isp[ans[cur-1]+ans[0]]){
            for (int i =0;i<n-1;i++){
                cout << ans[i] << " ";
            }
            cout << ans[n-1] << endl;
        }
        return;
    }
    for (int i =1;i<=n;i++){
        if (!vis[i] && isp[ans[cur-1]+i]) {
            vis[i] = 1;
            ans[cur] = i;
            search(n,cur+1);
            vis[i] = 0;
        }
    }
}

int main(){
    ifstream fin("input.txt");
    cin.rdbuf(fin.rdbuf());
    memset(isp,1,sizeof(isp));
    for (int i =2;i<MaxN;i++){
        for (int j =2;j<MaxN/i;j++){
            isp[i*j] = 0;
        }
    }
    int n ;
    int count=0;
    while (cin >> n){
        memset(vis,0,sizeof(vis));
        ans[0] = 1;
        vis[1] = 1;
        if (count!=0) {
            cout << endl;
        }
        count++;
        printf("Case %d:\n",count);
        search(n,1);
    }
}
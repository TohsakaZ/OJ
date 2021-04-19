#include <algorithm>
#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
const int maxW=20;
int n,m,k;
int dp[maxW][maxW][maxW][maxW];
int arr[maxW][maxW];
typedef vector<pair<int,int> > plist;
int DP(int lx,int ly,int rx,int ry){
    int rb=rx,re=lx,cb=ry,ce=ly;
    int& ans = dp[lx][ly][rx][ry];
    if (ans > -1){
        return ans;
    }
    //printf("%d %d %d %d\n",lx,ly,rx,ry);
    for (int i =lx;i<rx;i++){
        for (int j=ly;j<ry;j++){
            if (arr[i][j]>0){
                rb = min(rb,i);
                re = max(re,i);
                cb = min(cb,j);
                ce = max(ce,j);
            }
        }
    }
    if (rb==re&& cb==ce){
        return (ans=0);
    }
    //printf("%d %d %d %d\n",rb,re,cb,ce);
    ans = INT32_MAX;
    for (int i =rb+1;i<=re;i++){
        ans = min(ans,ry-ly+DP(lx,ly,i,ry)+DP(i,ly,rx,ry));
    }
    for (int j=cb+1;j<=ce;j++){
        ans = min(ans,rx-lx+DP(lx,ly,rx,j)+DP(lx,j,rx,ry));
    }
    return ans;
}

int main()
{
    int count=0;
    while (cin >> n >> m >> k){
        memset(arr,0,sizeof(arr));
        memset(dp,-1,sizeof(dp));
        for (int i =0;i<k;i++){
            int a,b;
            cin >> a >> b;
            arr[a-1][b-1] = 1;
        }
        count++;
        printf("Case %d: %d\n",count,DP(0,0,n,m));
    }
}
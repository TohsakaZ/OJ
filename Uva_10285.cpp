#include <iostream>
#include <cstring>

using namespace std;

const int MaxW = 110;
const int ra[4] = {-1,0,1,0};
const int ca[4] = {0,-1,0,1};
int M[MaxW][MaxW];
int dp[MaxW][MaxW];
int r,c;
int ans;

int DP(int i,int j){
    if (dp[i][j] > 0){
        return dp[i][j];
    }
    dp[i][j] = 1;
    for (int k=0;k<4;k++){
        int nexti = i+ra[k];
        int nextj = j+ca[k];
        if (nexti>=0 && nexti < r && nextj>=0 && nextj<c && M[nexti][nextj] < M[i][j]){
            dp[i][j] = max(dp[i][j],DP(nexti,nextj)+1);
        }
    }
    ans = max(ans,dp[i][j]);
    return dp[i][j];
}

int main()
{
    int case_n;
    cin >> case_n;
    for (int i =0;i<case_n;i++){
        string name;
        cin >> name;
        cin >> r >> c;
        memset(dp,0,sizeof(dp));
        for (int ri=0;ri<r;ri++){
            for (int ci=0;ci<c;ci++){
                int h;
                cin >> h;
                M[ri][ci] = h;
            }
        }
        ans = 1;
        for (int i=0;i<r;i++){
            for (int j =0;j<c;j++){
                ans = max(DP(i,j),ans);
            }
        }
        printf("%s: %d\n",name.c_str(),ans);
    }
}
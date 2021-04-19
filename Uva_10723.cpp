#include <iostream>
#include <cstring>
using namespace std;
const int MaxL=35;
int dp[MaxL][MaxL];
int64_t dp_unique[MaxL][MaxL];
string s1,s2;
int DP(int i,int j){
    int& ans=dp[i][j];
    if (ans>-1){
        return ans;
    }
    ans = 0;
    if (i==0 || j==0){
        dp_unique[i][j]=1;
        return ans=0;
    }
    if (s1[i-1]==s2[j-1]){
        ans = max(ans,DP(i-1,j-1)+1);
        dp_unique[i][j] = dp_unique[i-1][j-1];
    }
    else{
        ans=max(ans,DP(i-1,j));
        ans=max(ans,DP(i,j-1));
        if (dp[i-1][j]>dp[i][j-1]){
            dp_unique[i][j] = dp_unique[i-1][j];
        }
        else if (dp[i][j-1] > dp[i-1][j]){
            dp_unique[i][j] = dp_unique[i][j-1];
        }
        else{
            dp_unique[i][j] = dp_unique[i][j-1]+dp_unique[i-1][j];
        }
    }
    return ans;
}
int main()
{
    int n;
    cin >> n;
    getline(cin,s1);
    for (int i =0;i<n;i++){
        getline(cin,s1);
        getline(cin,s2);
        memset(dp,-1,sizeof(dp));
        memset(dp_unique,0,sizeof(dp_unique));
        int l1 = s1.length();
        int l2 = s2.length();
        int l3 = l1+l2-DP(l1,l2);
        printf("Case #%d: %d %ld\n",i+1,l3,dp_unique[l1][l2]);
    }

}
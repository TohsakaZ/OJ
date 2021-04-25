#include <iostream>
#include <cstring>
#include <vector>
using namespace std;
const int MaxL = 10000;
const int INF = 1e8;
int dp[MaxL][MaxL][2];
int cnt_time;
vector<pair<int, int> > treasure;
int dist(int i,int j){
    return abs(treasure[i].first - treasure[j].first);
}
int DP(int i,int j,int r){
    int &ans = dp[i][j][r];
    if (ans!=-1){
        return ans;
    }
    if (i == j){
        return ans=0;
    }
    if (r==0){
        ans = min(DP(i + 1, j, 0) + dist(i, i + 1), DP(i + 1, j, 1)+ dist(i, j));

        if (ans >= treasure[i].second){
            ans = INF;
        }
    }
    else{
        ans = min(DP(i, j - 1, 1) + dist(j, j - 1), DP(i, j - 1, 0)+ dist(i, j));
        if (ans >= treasure[j].second){
            ans = INF;
        }
    }
    return ans;
}
int main()
{
    int N;
    treasure.resize(MaxL);
    while (cin >> N)
    {
        for (int i = 0; i < N; i++)
        {
            cin >> treasure[i].first >> treasure[i].second;
        }
        for (int i = 0;i<N;i++){
            dp[i][i][0] = dp[i][i][1] = 0;
        }
        for (int i = 1; i < N;i++){
            for (int l = 0; l < N-i;l++){
                int r = l + i;
                dp[l][r][0] = min(dp[l + 1][r][0] + dist(l, l + 1), dp[l + 1][r][1] + dist(l, r));
                if (dp[l][r][0] >= treasure[l].second){
                    dp[l][r][0] = INF;
                }
                dp[l][r][1] = min(dp[l][r - 1][1] + dist(r, r - 1), dp[l][r - 1][0] + dist(l, r));
                if (dp[l][r][1] >= treasure[r].second){
                    dp[l][r][1] = INF;
                }
            }
        }
        int ans = min(dp[0][N - 1][0], dp[0][N - 1][1]);
        if (ans >= INF)
        {
            cout << "No solution" << endl;
        }
        else{
            cout << ans << endl;
        }
    }
}
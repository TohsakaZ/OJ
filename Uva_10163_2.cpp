#include <vector>
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;
const int MaxM = 32;
const int MaxN = 102;
const int INF = 1e8;
int P[MaxM];
int dp[MaxM][MaxN];
int dp_v[MaxM][MaxN];
int N, M;
int DP(int n, int work_set)
{
    int &ans = dp[n][work_set];
    int &v = dp_v[n][work_set];
    if (ans != -1)
    {
        return ans;
    }
    if (work_set==0){
        v = 0;
        return ans = INF;
    }
    if (n > M-1){
        v = 0;
        return ans = 0;
    }
    ans = -1;
    v = INF;
    for (int i = 0; i <= work_set; i++)
    {
        // select
        if (i>0){
            int new_ans = min(DP(n+1,work_set-i),int(P[n]/i));
            if (new_ans > ans || (new_ans == ans && (dp_v[n+1][work_set-i] + P[n] < v))) {
                ans = new_ans;
                v = dp_v[n + 1][work_set - i] + P[n];
            }
        }
        // no select
        else{
            int new_ans = DP(n + 1, work_set);
            if (new_ans > ans || (new_ans == ans && (dp_v[n+1][work_set] < v))){
                ans = new_ans;
                v = dp_v[n + 1][work_set];
            }
        }
    }
    //cout << n << "  " << work_set << endl
    //     << ans << " "  << v << endl;
    return ans;
}
int main()
{
    while (cin >> N >> M && N && M)
    {
        for (int i = 0; i < M;i++){
            cin >> P[i];
        }
        dp[0][0] = INF;
        dp_v[0][0] = 0;
        for (int i = 1;i<=M;i++){
            dp[i][0] = INF;
            dp_v[i][0] = 0;
        }
        for (int i = 1; i <= N; i++)
        {
            dp[0][i] = 0;
            dp_v[0][i] = INF;
        }
        for (int i = 1; i <= M; i++)
        {
            for (int j = 1; j <=N;j++){
                dp[i][j] = dp[i - 1][j];
                for (int k = 1; k <= j;k++){
                    int new_ans = min(dp[i - 1][j - k], P[i - 1] / k);
                    if (new_ans > dp[i][j] ){
                        dp[i][j] = new_ans;
                    }
                }
            }
        }
        for (int i = 1; i <= M;i++){
            for (int j = 1; j <= N;j++){
                dp_v[i][j] = dp_v[i - 1][j];
                for (int k = 1; k <= j; k++)
                {
                    if (P[i-1]/k >= dp[M][N]){
                        dp_v[i][j] = min(dp_v[i][j], dp_v[i - 1][j - k] + P[i - 1]);
                    }
                }
            }
        }
        cout << dp[M][N] << " " << ((dp[M][N]==0)?0:dp_v[M][N]) << endl;
        //cout << DP(0, N) << " " << dp_v[0][N] << endl;
    }
}
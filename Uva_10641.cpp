#include <iostream>
#include <cstring>
using namespace std;
const int MaxN = 30;
const int MaxM = 1000;
const int INF = 1e8;
pair<int, int> point[MaxN];
pair<int, int> light[MaxM];
int dp[MaxM][maxN];
int MaxX, MaxY, MinX, MinY;
int val[MaxM];
int N, M;

pair<int,int> find_edge(int x,int y){
    int min_k = INF,min_id;
    int max_k = -INF,max_id;
    for (int i = 0; i < N; i++)
    {
        if (point[i].second == x){
            if (min_k == INF){
                min_id = i;
            }
            if (max_k == -INF){
                max_id = i;
            }
        }
        int k = point[i].second - y / point[i].second - x;
        if (x > MaxX || x < MinX){
            if (k < min_k){
                min_k = k;
                min_id = i;
            }
            if (k > max_k){
                max_k = k;
                max_id = i;
            }
        }
        else{
            if (k>=0 && k< min_k){
                min_k = k;
                min_id = i;
            }
            else if(k>max_k){
                max_k = k;
                max_id = k;
            }
        }
    }
    return make_pair(max_k, min_k);
}
int main()
{
    while (cin >> N && N){
        MinX = MinY = 10000;
        MaxX = MaxY = -10000;
        for (int i = 0; i < N; i++)
        {
            cin >> point[i].first >> point[i].second;
            MaxX = max(MaxX, point[i].first);
            MinX = min(MinX, point[i].first);
            MaxY = max(MaxY, point[i].second);
            MinY = min(MinY, point[i].second);
        }
        cin >> M;
        for (int i = 0; i < M;i++){
            int x, y;
            cin >> x >> y >> val[i];
            light[i] = find_edge(x, y);
        }
        memset(dp, -1, sizeof(dp));
        int beg_i = light[0].first;
        for (int j = light[0].first; j < light[0].second;j=(j+1)%N){
            dp[0][j - beg_i] = val[0];
        }
        for (int i = 1; i < M; i++)
        {
            int pi = (beg_i + i) % M;
            int jmin = (light[pi].first - beg_i + N) % N;
            int jmax = (light[pi].second -beg_i + N )% N;
            for (int j = jmin; j < jmax;j=(j+1)%N){
                // don't choose
                if (dp[i-1][j]!=-1){
                    dp[i][j] = dp[i - 1][j];
                }
                // if choose
                int prej = (jmin - 1 + N) % N;
                if (dp[i-1][prej]!=-1){
                    if (dp[i][j] == -1) {
                        dp[i][j] = dp[i - 1][prej] + val[i];
                    }
                    else{
                        dp[i][j] = min(dp[i][j], dp[i - 1][prej] + val[i]);
                    }
                }
            }
        }
        cout << dp[M - 1][N - 1] == -1 ? "Impossible" : dp[M - 1][N - 1];
    }
}
#include <iostream>
#include <vector>
#include <set>
using namespace std;
const int MaxN = 101;
const int MaxM = 30;
const int INF = 1e9;
vector<int> P;
vector<pair<int,vector<int> >  > dp;
vector<vector<int> > bnum;
int main()
{
    P.resize(MaxM);
    dp.resize(1 << (MaxM-1));
    bnum.resize(MaxM);
    int N, M;

    // intit bnum size
    bnum[0].clear();
    bnum[0].push_back(0);
    for (int i = 0; i < MaxM; i++)
    {
        // insert next loc
        bnum[i + 1].clear();
        for (auto &item : bnum[i])
        {
            for (int k = 0; k < M; k++)
            {
                if ((item >> k) & 1)
                {
                    continue;
                }
                bnum[i + 1].push_back(item | (1 << k));
            }
        }
    };
    while (cin >> N >> M && N != 0 && M != 0)
    {
        for (int i = 0; i < M; i++)
        {
            cin >> P[i];
        }
        dp[0].first = 0;
        dp[0].second = vector<int>(M, 0);
        int last_ans;
        for (int i = 0; i < N; i++)
        {
            // cycle num loc
            for (int k = min(i+1,M); k > 0; k--)
            {
                for (auto &item : bnum[k])
                {
                    pair<int, vector<int>> ans;
                    ans.first = 0;
                    // from new
                    for (int j = 0; j < M; j++)
                    {
                        if ((item >> j) & 1)
                        {
                            int son_num = item ^ (1 << j);
                            int new_line = min(dp[son_num].first, P[j]);
                            if (ans.first < new_line)
                            {
                                ans.first = new_line;
                                ans.second = dp[son_num].second;
                                ans.second[j] = 1;
                            }
                        }
                    }
                    if (k < i + 1)
                    {
                        // from old
                        for (int j = 0; j < M; j++)
                        {
                            if ((item >> j) & 1)
                            {
                                int new_line = min(dp[item].first, P[j] / (dp[item].second[j] + 1));
                                if (ans.first < new_line)
                                {
                                    ans.first = new_line;
                                    ans.second = dp[item].second;
                                    ans.second[j]++;
                                }
                            }
                        }
                    }
                    dp[item] = ans;
                    if (i==N-1){
                        last_ans = max(last_ans, ans.first);
                    }
                }
            }
        }
        cout << last_ans << endl;
    }
}
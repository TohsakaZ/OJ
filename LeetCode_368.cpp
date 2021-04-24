#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <unordered_map>

using namespace std;
vector<int> edge[1001];
int dp[1001];

int DP(int  n ){
    if (dp[n]>0){
        return dp[n];
    }
    dp[n] = 1;
    int max_ans = 0;
    for (int i = 0;i<edge[n].size();i++){
        max_ans = max(max_ans,DP(edge[n][i]));
    }
    dp[n] += max_ans;
    return dp[n];
}
vector<int> largestDivisibleSubset(vector<int>& nums){
    sort(nums.begin(),nums.end());
    memset(dp,0,sizeof(dp));
    for (int i =0;i<nums.size()-1;i++){
        for (int j =i+1;j<nums.size();j++){
            if (nums[j] % nums[i] == 0){
                edge[i].push_back(j);
            }
        }
    }
    DP(0);
    int max_num = 0;
    int beg_cnt = 0;
    for (int i =0;i<nums.size();i++){
        if (DP(i) > max_num) {
            max_num = DP(i);
            beg_cnt = i;
        }
    }
    vector<int> ans;
    int cnt=beg_cnt;
    while (dp[cnt] > 1){
        for (int i =0;i<edge[cnt].size();i++){
            if (dp[edge[cnt][i]] == dp[cnt] - 1){
                ans.push_back(nums[cnt]);
                cnt = edge[cnt][i];
                break; 
            }
        }
    }
    ans.push_back(nums[cnt]);
    return ans;
}

int main()
{
    vector<int> input;
    int n;
    while (cin >> n){
        input.clear();
        for (int i =0;i<n;i++){
            int temp;
            cin >> temp;
            input.push_back(temp);
        }
        for (auto item: largestDivisibleSubset(input)){
            cout << item << " " ;
        }
        cout << endl;
    }
}
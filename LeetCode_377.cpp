#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;

unsigned int dp[1001];

int combinationSum4(vector<int>& nums, int target) {
    sort(nums.begin(),nums.end());
    memset(dp,0,sizeof(dp));
    dp[0] = 1;
    for (int i =0;i<target;i++){
        for (int j =0;j<nums.size();j++){
            if (int64_t(nums[j]+ i) <=target ){
                dp[nums[j]+i]+=dp[i];
            }
            else{
                break;
            }
        }
    }
    return dp[target];
}

int main()
{
    int n,t;
    vector<int> nums;
    cin >>  n >> t;
    for (int i =0;i<n;i++){
        int temp;
        cin >> temp;
        nums.push_back(temp);
    }
    cout << combinationSum4(nums,t) << endl;

}
#include <stdio.h>
#include <iostream>
#include <set>
#include <cstring>
using namespace std;
const int max_S= 15;
const int max_Value= 5000;
set<int> stamp_set;
int dp[max_Value];
bool compare(set<int>& s1,set<int>& s2){
    if (s1.size() != s2.size()){
        return s1.size() < s2.size();
    }
    auto beg1 = s1.rbegin();
    auto beg2 = s2.rbegin();
    while (beg1!=s1.rend() && beg2 != s2.rend() && *beg1==*beg2){
        beg1++;
        beg2++;
    }
    return  beg1==s1.rend() ? false:*beg1<*beg2;
}
int main()
{
    int S;
    while (cin >> S && S!=0){
        int N;
        cin >> N;
        int max_coverage=-1;
        set<int> ans;
        for (int case_i =0;case_i<N;case_i++){
            int k;
            cin >> k;
            stamp_set.clear();
            for (int case_j=0;case_j<k;case_j++){
                int temp;
                cin >>  temp;
                stamp_set.insert(temp);
            }
            memset(dp,0,sizeof(dp));
            dp[0] = 0;
            for (int i =1;i<=max_Value;i++){
                dp[i]=INT32_MAX;
                for (auto& item:stamp_set){
                    if (item>i){
                       break; 
                    }
                    if (dp[i-item] < S){
                        dp[i] = min(dp[i],dp[i-item]+1);
                    }
                }
                if (dp[i] == INT32_MAX){
                    if (i-1 > max_coverage || i-1==max_coverage && compare(stamp_set,ans)){
                        ans = stamp_set; 
                        max_coverage = i-1;
                    }
                    break;
                }
            }
        }
        printf("max coverage =%4d :",max_coverage);
        for (auto& item: ans){
            printf("%3d",item);
        }
        cout << endl;
    }

}
#include <iostream>
#include <fstream>
#include <stack>
#include <cstring>

using namespace std;

int n;
const int MaxN = 100010;
int arr[MaxN];
int64_t sum[MaxN];
int ll[MaxN];
int rr[MaxN];
int64_t ans;
int ans_l,ans_r;


int main()
{
    ifstream fin("input.txt");
    cin.rdbuf(fin.rdbuf());
    int case_n=0;
    while (cin >> n){
        if (case_n){
            cout << endl;
        }
        case_n++;
        sum[0]=0;
        for  (int i =0;i<n;i++){
            cin >> arr[i];
            sum[i+1] = sum[i]+arr[i];
        }
        ans = -1;
        stack<int> s;
        for (int i=0;i<n;i++){
            while (!s.empty() && arr[s.top()] >= arr[i]){
                rr[s.top()] = i-1;
                s.pop();
            }
            if (s.empty()){
                ll[i] = 0;
            }
            else{
                ll[i] = s.top()+1;
            }
            s.push(i);
        }
        while (!s.empty()){
            rr[s.top()]=n-1;
            s.pop();
        }
        for (int i =0;i<n;i++){
            int64_t v =  (sum[rr[i]+1]-sum[ll[i]]) * arr[i];
            if (v>ans){
                ans = v;
                ans_l = ll[i];
                ans_r = rr[i];
            }
            else if (v == ans){
                if ((rr[i]-ll[i] < ans_r-ans_l) || (ll[i]<ans_l && rr[i]-ll[i] == ans_r-ans_l)){
                    ans_l=ll[i];
                    ans_r = rr[i];
                }
            }
        }
        cout << ans << endl;
        cout << ans_l+1 << " "<< ans_r+1 << endl;
    }
}
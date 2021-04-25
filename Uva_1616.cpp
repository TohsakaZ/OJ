#include <iostream>
#include <fstream>
#include <algorithm>
#include <math.h>

using namespace std;


class point
{
public:
    int x,y;
};

int n;
const int MaxN = 100000;
const long double exp_d = 1e-10;
point arr[MaxN];

bool judge(long double ans){
    long double cnt = 0.0;
    for (int i = 0; i < n; i++)
    {
        cnt = max(cnt, (long double)arr[i].x);
        cnt += ans;
        if (cnt > arr[i].y){
            return false;
        }
    }
    return true;
}

int  main(){
    ifstream fin("input.txt");
    cin.rdbuf(fin.rdbuf());

    while (cin >> n)
    {
        for (int i =0;i<n;i++){
            cin >> arr[i].x >> arr[i].y;
        }
        sort(arr,arr+n,[](point l,point r) ->bool{ return l.x < r.x || (l.x == r.x && l.y < r.y);});
        long double ans = 0;
        long double l = 0.0;
        long double r = 1000000.0;
        while ( r-l > exp_d){
            ans = (l + r) / 2.0;
            if (judge(ans)){
                l = ans;
            }
            else{
                r = ans;
            }
        }
        // convert 
        ans =l;
        int p,q; 
        int ans_p = 0,ans_q=1;
        for (q=1;q<=n;q++){
            p = round(q*ans);
            if (fabs(ans- (long double)p/q) <  fabs(ans-(long double)ans_p/ans_q)){
                ans_p = p;
                ans_q = q;
            }
        }
        cout << ans_p << "/" << ans_q << endl;
    }
}
#include <iostream>
using namespace std;
const int maxL=1001;
int pre[1000];
int dp[maxL][maxL];
int arr[maxL];
int main()
{
    // preprocess
    for (int i=0;i<1000;i++){
        if (i<10){
            pre[i] = min(i,10-i);
        }
        else if (i<100){
            int a=i/10;
            int b=i-a*10;
            pre[i]=pre[a]+pre[b];
            int move = min(abs(a-b),10-abs(a-b));
            pre[i]=min(pre[i],move+pre[a]);
            pre[i]=min(pre[i],move+pre[b]);
        }
        else {
            int a=i/100;
            int b=(i-a*100)/10;
            int c=i-a*100-b*10;
            pre[i] = pre[a]+pre[b]+pre[c];
            pre[i] = min(pre[i],pre[a*10+b]+pre[c]);
            pre[i] = min(pre[i],pre[a]+pre[b*10+c]);
            int move1 = min(abs(a-b),10-abs(a-b));
            int move2 = min(abs(a-c),10-abs(a-c));
            int move3 = min(abs(b-c),10-abs(b-c));
        }
    }
    string s1,s2;
    while (cin >> s1 >> s2){
        int l = s1.length();
        for (int i =0;i<l;i++){
            arr[i]=(s1[i]-s2[i]+10) % 10;
        }
        for (int i =0;i<l;i++){
            dp[i][i+1]=min(arr[i],10-arr[i]);
        }
        for (int i =0;i<l;i++){
            for (int j=2;j<=l;j++){
                // (i,i+j)  (i,k) (k+d,i+j)
                for (int k =i+1;k<i+j;k++){
                    
                }
            }
        }
    }
    

}
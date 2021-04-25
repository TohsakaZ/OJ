#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <algorithm>


using namespace std;

int N,K,M;
const int MaxN = 1000001;
const int MaxK = 111;
int arr[MaxN];
int vis[MaxN];

int main(){
    ifstream fin("input.txt");
    cin.rdbuf(fin.rdbuf());

    arr[0]=1;
    arr[1]=2;
    arr[2]=3;
    int case_n;
    cin >> case_n;
    for (int case_i=0;case_i<case_n;case_i++){
        cin >> N >> M >> K;
        memset(vis,0,sizeof(vis));
        vector<int> record;
        vector<vector<int> > k(K+1);
        for (int i = 0; i < 3;i++){
            arr[i] = i + 1;
            if (arr[i] <=K){
                vis[arr[i]]++;
                record.push_back(i);
                k[arr[i]].push_back(i);
            }
        } 
        vis[1] = vis[2] = vis[3] = 1;
        for (int i =3;i<N;i++){
            arr[i] = (arr[i-1]+arr[i-2]+arr[i-3]) % M +1;
            if (arr[i] <= K){
                vis[arr[i]]++;
                record.push_back(i);
                k[arr[i]].push_back(i);
            }
        }
        bool flag =true;
        for (int i =1;i<=K;i++){
            if (!vis[i]){
               flag =false;
               break; 
            }
        }
        if (!flag){
            printf("Case %d: sequence nai\n",case_i+1);
            continue;
        }
        int ans = INT32_MAX;
        for (int i =0;i<=record.size();i++){
            int min_right = record[i];
            bool flag =true;
            for (int j =1;j<=K;j++){
                if (j == arr[record[i]] ){
                    continue;
                }
                auto find_iter = upper_bound(k[j].begin(),k[j].end(),record[i]);
                if (find_iter == k[j].end()){
                    flag =false;
                    break;
                }
                min_right = max(min_right,*find_iter);
            }
            if (!flag){
                break;
            }
            ans = min(ans,min_right-record[i]+1);
        }
        printf("Case %d: %d\n",case_i+1,ans);
    }
}

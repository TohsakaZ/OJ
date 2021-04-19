/*
memset初始化不能用1 因为是按一个字节去复制的。。。
*/
#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;
const int MaxP=1000;
const int INF = 1e8;
int p[MaxP];
int num[MaxP];
class edge
{
public:
    int p1,p2;
    int weight;
    bool operator<(const edge& Other)const{
        return this->weight < Other.weight;
    }
};
vector<edge> e_list;
int n,m;
void init(){
    for (int i=0;i<=n;i++){
        num[i] =1;
        p[i] = i;
    }
}
int find(int i){
    return p[i] == i? i : p[i]=find(p[i]);
}
int main()
{
    while (cin >> n >> m && (n+m)!=0){
        // read input
        e_list.clear();
        for (int i =0;i<m;i++){
            edge k;
            cin >> k.p1>> k.p2 >> k.weight;
            e_list.push_back(k);
        }
        sort(e_list.begin(),e_list.end());
        int ans = INF;
        int beg_i = 0;
        while (beg_i<e_list.size()){
            bool flag = true;
            init();
            for (int i=beg_i;i<e_list.size();i++){
                int a = find(e_list[i].p1);
                int b = find(e_list[i].p2);
                if (a==b){
                    continue;
                }
                p[b] = a; 
                num[a]+=num[b];
                if (num[a] == n){
                    ans = min(ans,e_list[i].weight-e_list[beg_i].weight);
                    flag=false;
                    break; 
                }
            }
            if (flag){
                break;
            }
            beg_i++;
        }
        // 
        if (ans==INF){
            cout << -1 << endl;
        }
        else{
            cout << ans << endl;
        }
        
    }
}
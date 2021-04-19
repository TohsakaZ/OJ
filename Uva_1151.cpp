#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
const int MaxQ=10;
const int MaxN=1010;
int n,q;
vector<int> qset[MaxQ];
int qvalue[MaxQ];
int p[MaxN];
int ans;
class edge
{
public:
    int p1,p2;
    int weight;

    bool operator<(const edge&Other) const{
        return this->weight < Other.weight;
    }
};
vector<edge> e_list;

int dist2(pair<int,int> p1,pair<int,int> p2){
    return (p1.first-p2.first)*(p1.first-p2.first)+(p1.second-p2.second)*(p1.second-p2.second);
}
int find(int i){
    return p[i]==i?i:p[i]=find(p[i]);
}
int init(int s){
    for (int i =1;i<=n;i++){
        p[i] = i;
    }
    int v=0;
    for (int i=0;i<q;i++){
        if (s &(1<<i)) {
            v+= qvalue[i];
            for (int j=0;j<qset[i].size()-1;j++){
                int k1 = qset[i][j];
                int k2 = qset[i][j+1];
                int f1 = find(k1);
                int f2 = find(k2);
                if (f1==f2){
                    continue;
                }
                p[f2] = f1;
            }
        }
    }
    return v;
}

void find_ans(const vector<edge>& el){
    int v;
    for (int i =1;i<(1<<q);i++){
        v = init(i); 
        for (auto& item: el){
            int f1 = find(item.p1);
            int f2 = find(item.p2);
            if (f1==f2) {
                continue;
            }
            p[f2]=f1;
            v+= item.weight;
        }
        ans = min(v,ans);
    }
}

int main()
{
    int case_num;
    cin >> case_num;
    for (int case_i=0;case_i<case_num;case_i++){
        if (case_i){
            cout << endl;
        }
        cin >> n >> q;
        for (int i =0;i<q;i++){
            qset[i].clear();
            int k;
            cin >> k >> qvalue[i];
            for (int j=0;j<k;j++){
                int temp;
                cin >>  temp;
                qset[i].push_back(temp);
            }
        }
        vector<pair<int,int> > p_list;
        e_list.clear();
        for (int i=0;i<n;i++){
            int x,y;
            cin >> x>> y;
            p_list.push_back(make_pair(x,y));
            for (int j=0;j<=i;j++){
                edge temp;
                temp.p1 = i+1;
                temp.p2 = j+1;
                temp.weight = dist2(p_list[i],p_list[j]);
                e_list.push_back(temp);
            }
        }
        sort(e_list.begin(),e_list.end());
        vector<edge> new_e_list;
        init(0);
        ans = 0;
        for (auto& item:e_list){
            int f1=find(item.p1);
            int f2=find(item.p2);
            if (f1==f2){
                continue;
            }
            p[f2]=f1;
            new_e_list.push_back(item);
            ans+=item.weight;
            if (new_e_list.size() == n-1){
                break;
            }
        }
        find_ans(new_e_list);
        cout << ans << endl;
    }

}
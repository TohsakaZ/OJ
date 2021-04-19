#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <queue>
using namespace std;
int n,m;
unordered_map<int,int> d;
class edge
{
public:
    int w;
    string prefix;
    string post;

    int install(int input){
        for (int i =0;i<n;i++) {
            if (prefix[i] =='+' && ((input>>i)&1)==0){
                return -1; 
            }
            else if (prefix[i] =='-' && ((input>>i)&1)==1){
                return -1;
            }
            if (post[i] == '+'){
                input = input | (1<<i);
            }
            else if (post[i] == '-' && ((input>>i)&1) == 1){
                input = input ^ (1<<i);
            }
        }
        return input;
    }
    
    friend istream& operator>>(istream& os,edge& e){
        os >> e.w >> e.prefix >> e.post;
        return os;
    }
};
vector<edge> elist;
int dijskra(){
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> q;
    d[(1<<n)-1] = 0;
    q.push(make_pair(0,(1<<n)-1));
    while (!q.empty()){
        auto cnt = q.top();
        q.pop();
        if (cnt.second == 0){
            return cnt.first;
        }
        if (d[cnt.second] != cnt.first){
            continue;
        }
        for (auto& e:elist){
            int next = e.install(cnt.second);
            if (next == -1){
                continue;
            }
            if (d.count(next) && d[next] <= cnt.first+e.w){
                continue;
            }
            d[next] = cnt.first+e.w;
            q.push(make_pair(d[next],next));
        }
    }
    return -1;
}
int main(){
    int case_n=0;
    while (cin >> n >> m && (n+m)){
        d.clear();
        elist.clear();
        case_n++;
        for (int i =0;i<m;i++){
            edge e;
            cin >> e;
            elist.push_back(e);
        }
        int ans = dijskra();
        printf("Product %d\n",case_n);
        if (ans == -1){
            cout << "Bugs cannot be fixed." << endl;
        }
        else{
            printf("Fastest sequence takes %d seconds.\n",ans);
        }
        cout << endl;
    }
}
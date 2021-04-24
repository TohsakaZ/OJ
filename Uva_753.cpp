#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <cstring>
#include <queue>
#include <vector>

using namespace std;
const int max_point = 410;
const int INF_FLOW = 10000;
class edge
{
public:
    edge(int from,int to ,int cap,int flow):from(from),to(to),cap(cap),flow(flow){}
    int from,to,cap,flow;
};
int n,m,k;
int max_table=0;
unordered_map<string,vector<int>> table_out;
unordered_map<string,vector<int>> table_in;
unordered_map<string,int> table_connect_in;
unordered_map<string,int> table_connect_out;
vector<int> m_edge[max_point];
vector<edge> edges;
int a[max_point];
int f[max_point];
void init(){
    table_connect_in.clear();
    table_connect_out.clear();
    table_in.clear();
    table_out.clear();
    edges.clear();
    for (int i =0;i<max_table;i++){
        m_edge[i].clear();
    }
}
void add_edge(int idx1,int idx2,int cap){ 
    edges.push_back(edge(idx1,idx2,cap,0));
    edges.push_back(edge(idx2,idx1,0,0));
    m_edge[idx1].push_back(edges.size()-2);
    m_edge[idx2].push_back(edges.size()-1);
}
int get_id(string str,unordered_map<string,int>& table){
    if (!table.count(str)){
        table[str] = max_table;
        max_table++;
    }
    return table[str];
}
int find_maxFlow(int beg,int end){
    int ans_flow = 0;
    while (true){
        memset(a,0,sizeof(a));
        memset(f,0,sizeof(f));
        queue<int> q;
        q.push(beg);
        f[beg] = -1;
        a[beg] = INF_FLOW;
        while (!q.empty()){
            int cnt = q.front();
            //cout << "cnt " << cnt << endl;
            q.pop();
            for (auto edge_id: m_edge[cnt]){
                auto& cnt_edge = edges[edge_id];  
                if ( !a[cnt_edge.to] && cnt_edge.flow < cnt_edge.cap){
                    a[cnt_edge.to]  = min(a[cnt],cnt_edge.cap-cnt_edge.flow);
                    f[cnt_edge.to] = edge_id;
                    q.push(cnt_edge.to);
                }
            }
            if (a[end]){
                break;
            }
        }
        if (!a[end]){
            break;
        }
        int cnt = end;
        while (f[cnt]!=-1){
            int cnt_edge_id =f[cnt];
            edges[cnt_edge_id].flow += a[end];
            edges[cnt_edge_id^1].flow -= a[end];
            cnt = edges[cnt_edge_id].from;
        }
        ans_flow += a[end];
    }
    return ans_flow;
}
int main()
{
    int case_n;
    cin >> case_n;
    int case_i=0;
    while (case_i < case_n){
        if (case_i){
            cout << endl;
        }
        init();
        max_table = 2;
        cin >> n;
        for (int i =0;i<n;i++){
            string str;
            cin >> str;
            int idx = max_table;
            table_out[str].push_back(idx);
            max_table++;
            add_edge(idx,1,1);
        }
        cin >> m;
        for (int i =0;i<m;i++){
            string temp,str;
            cin >> temp >> str;
            int idx = max_table;
            table_in[str].push_back(idx);  
            max_table++;
            add_edge(0,idx,1);
        }
        for (auto& item: table_in){
            if (table_out.count(item.first)){
                for (auto idx1: item.second){
                    for (auto idx2: table_out[item.first]){
                        add_edge(idx1,idx2,1);
                    }
                }
            }
        }
        cin >> k;
        for (int i =0;i<k;i++){
            string str1,str2;            
            cin >> str1 >> str2;
            int idx1 = get_id(str1,table_connect_in);
            int idx2 = get_id(str2,table_connect_out);
            add_edge(idx1,idx2,INF_FLOW);
        }
        // idx_in to connect_in
        for (auto& item: table_in){
            if (table_connect_in.count(item.first)) {
                for (auto idx1: item.second){
                    int idx2 = table_connect_in[item.first];
                    add_edge(idx1,idx2,1);
                }
            }
        }
        // idx_out to connect_out
        for (auto& item:table_out){
            if (table_connect_out.count(item.first)){
                int idx1 = table_connect_out[item.first];
                for (auto idx2: item.second){
                    add_edge(idx1,idx2,1);
                }
            }
        }
        // connect_out ot connect_in
        for (auto& item:table_connect_out){
            if (table_connect_in.count(item.first)){
                int idx1 = item.second;
                int idx2 = table_connect_in[item.first];
                add_edge(idx1,idx2,INF_FLOW);
            }
        }
        cout << m - find_maxFlow(0,1) << endl;
        case_i++;
    }
}
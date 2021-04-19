#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <cstring>

using namespace std;
const int MaxN = 30;
int M[MaxN][MaxN];
int f[MaxN];
int n,m;
map<string,int> set_name;
vector<string> vec_name;
string get_name(int i){
    return vec_name[i];
}
int get_id(string name){
    if (set_name.count(name)==0){
        vec_name.push_back(name);
        set_name[name]= vec_name.size()-1;
    }
    return set_name[name];
}
void clear_name(){
    set_name.clear();
    vec_name.clear();
}

int find_s(int i){
    return f[i]==i?i:f[i]=find_s(f[i]);
}

void floyd(){
    for (int k=0;k<n;k++){
        for (int i=0;i<n;i++){
            for (int j=0;j<n;j++){
                M[i][j] = M[i][j] || (M[i][k] && M[k][j]);
            }
        }
    }
    for (int i =0;i<n-1;i++){
        for (int j=i+1;j<n;j++){
            if (M[i][j] && M[j][i]){
                int fi = find_s(i);
                int fj = find_s(j);
                if (fi != fj){
                    f[fi] = f[fj];
                }
            }
        }
    }
}
int main(){
    int case_n=0;
    while (cin >> n >> m && n && m){
        if (case_n){
            cout << endl;
        }
        case_n++;
        for (int i =0;i<n;i++){
            f[i] = i;
        }
        clear_name();
        memset(M,0,sizeof(M));
        for (int i =0;i<m;i++){
            string a,b;
            cin >> a >> b;
            int a1 = get_id(a);
            int b1 = get_id(b);
            M[a1][b1] = 1;
        }
        floyd();
        map<int,vector<string> > ans;
        for (int i=0;i<n;i++){
            int fi = find_s(i);
            ans[fi].push_back(get_name(i));
        }
        printf("Calling circles for data set %d:\n",case_n);
        for (auto& item:ans){
            for (int i =0;i<item.second.size();i++){
                if (i){
                    cout << ", ";
                }
                cout << item.second[i];
            }
            cout << endl;
        }
    }
}
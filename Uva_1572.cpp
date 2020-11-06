#include <iostream>
#include <fstream>
#include <set>
#include <vector>
#include <cstring>

using namespace std;

int M[52][52];
int idx[52];
vector<int> exist;

int char2idx(const char* c){
    if (c[0] == '0' ){
        return -1;
    }
    int i = c[0] - 'A';
    if (c[1] == '-'){
        i += 26;
    }
    return i;
}

int transidx(int idx){
    if (idx < 26){
        idx += 26;
    }
    else{
        idx -= 26;
    }
    return idx;
}

bool dfs(int now){
    idx[now] = -1;
    for (int i = 0; i < exist.size();i++){
        if (M[now][exist[i]]==0 ){
            continue;
        }
        int next = transidx(exist[i]);
        if (idx[next] == -1){
            return true;
        }
        if (idx[next] == 0 && dfs(next)){
            return true;
        }
    }
    idx[now] = 1;
    return false;
}

bool topo(){
    for (auto i : exist){
        if (dfs(i)){
            return true;
        }
    }
    return false;
}

int main()
{
    ifstream fin("input.txt");
    cin.rdbuf(fin.rdbuf());
    int type_number;
    while (cin >>  type_number){
        memset(M, 0, sizeof(M));
        memset(idx, 0, sizeof(idx));

        set<int> exist_find;
        for (int i = 0; i < type_number; i++)
        {
            string templine;
            cin >> templine;
            int a[4];
            for (int k = 0; k < 4;k++){
                a[k] = char2idx(templine.substr(k * 2, 2).c_str());
                if (a[k]!=-1){
                    exist_find.insert(a[k]);
                    for (int l = 0; l < k; l++)
                    {
                        if (a[l]!=-1){
                            M[a[k]][a[l]] = 1;
                            M[a[l]][a[k]] = 1;
                        }
                    }
                }
            }
        }
        exist = vector<int>(exist_find.begin(), exist_find.end());
        if (topo()){
            cout << "unbounded" << endl;
        }
        else{
            cout << "bounded" << endl;
        }

    }
}

#include <iostream>
#include <vector>
#include <fstream>
#include <cstring>

using namespace std;

const int MaxN=6;
class tree
{
public:
    double l=0;
    double r=0;
};

vector<tree>  t[1<<MaxN]; //记录对应二进制子集所有二叉数的l和r的宽度

int vis[1<<MaxN];
int sum[1<<MaxN]; //记录所有二进制子集对应的重量
int w[MaxN];

double r;
int s;

void dfs(int set_num){
    if (vis[set_num]){
        return;
    }
    vis[set_num] = 1;
    
    int subset = (set_num-1)&set_num;
    if (subset==0){
        t[set_num].push_back(tree()); 
        return;
    }
    for (;subset>0;subset=(subset-1)&set_num){ // 求某个特定二进制值对应的所有子集 相当于遍历1-subset之间的值 & 用于确保是子集
        int left = subset;
        int right = left ^ set_num;
        dfs(left);
        dfs(right);
        double len_left = (double)sum[right] / sum[set_num];
        double len_right = (double)sum[left] / sum[set_num];
        for (int tl=0;tl<t[left].size();tl++){
            for (int tr=0;tr<t[right].size();tr++){
                tree new_tree;
                new_tree.l = max(t[left][tl].l+len_left,t[right][tr].l-len_right);
                new_tree.r = max(t[right][tr].r+len_right,t[left][tl].r-len_left);
                if (new_tree.l+new_tree.r > r){
                   continue; 
                }
                t[set_num].push_back(new_tree);
            }
        }
    }
}

int main(){
    ifstream fin("input.txt");
    cin.rdbuf(fin.rdbuf());

    int num_case;
    cin >> num_case;
    while (num_case--){
        memset(vis,0,sizeof(vis));
        cin >> r >> s;
        for (int i=0;i<s;i++){
            cin >> w[i];
        }
        for (int i=1;i<(1<<s);i++){
            t[i].clear();
            sum[i] = 0;
            for (int j=0;j<s;j++){
                if (i&(1<<j)){
                    sum[i]+=w[j];
                }
            }
        }

        int root = (1<<s) - 1;
        dfs(root);
        double max_ans = -1;
        for (int i =0;i<t[root].size();i++){
            max_ans = max(max_ans,t[root][i].l+t[root][i].r);
        }
        if (max_ans<0){
            printf("-1\n");
        }
        else{
            printf("%.10lf\n",max_ans);
        }
    }
}
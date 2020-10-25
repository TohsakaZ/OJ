#include <iostream>
#include <fstream>
#include <cstring>
#include <math.h>

using namespace std;
const int Maxn = 2000;

char tree[Maxn];
int link[Maxn][4];
int top = 0;

void build_tree(int head){
    char c;
    cin >> c;
    if (c == 'p'){
        if (tree[head] !='f' ){
            tree[head] = 'p';
        }
        for (int i = 0; i < 4;i++){
            if (link[head][i] ==-1){
                link[head][i] = ++top;
            }
            build_tree(link[head][i]);
        }
    }
    else if (c=='f'){
        tree[head] = 'f';
    }
    return;
}

int compute_tree(int head,int deep){
    if (tree[head] == 'e'){
        return 0;
    }
    else if (tree[head]=='f'){
        return pow(2, 5 - deep) * pow(2, 5 - deep);
    }
    else if (tree[head] == 'p'){
        int sum = 0;
        for (int i = 0; i < 4; i++)
        {
            sum += compute_tree(link[head][i],deep+1);
        }
        return sum;
    }
}

int main()
{
    ifstream fin("input.txt");
    cin.rdbuf(fin.rdbuf());
    int case_n;
    cin >> case_n;
    while (case_n-- ){
        top = 0;
        memset(link, -1, sizeof(link));
        memset(tree, 'e', sizeof(tree));
        //first all white
        tree[0] = 'e';

        //cout << compute_tree(0, 0) << endl;
        build_tree(0);
        //cout << compute_tree(0, 0) << endl;
        build_tree(0);

        printf("There are %d black pixels.\n", compute_tree(0, 0));
        //cout << compute_tree(0,0) << endl;
    }
}
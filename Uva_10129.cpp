#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>

using namespace std;

int  M[26][26];
int num[26];
int visitd[26];
int exist[26];

int char_order(char a){
    return a - 'a';
}

void dfs(int n){
    for (int i =0;i<26;i++){
        if (exist[i] && !visitd[i] && (M[n][i] || M[i][n])){
            visitd[i] = 1; 
            dfs(i);
        }
    }
}
bool sovle(){
    int cnt =0;
    memset(visitd,0,sizeof(visitd));
    for (int i =0;i<26;i++){
        if (exist[i] && !visitd[i]){
            if (cnt>0){
                return false;
            }
            visitd[i] = 1;
            dfs(i);
            cnt++;
        }
    }
    return true;
}

int main()
{
    ifstream fin("input.txt");
    cin.rdbuf(fin.rdbuf());
    int case_n;
    cin >> case_n;
    while (case_n--){
        memset(M,0,sizeof(M));
        memset(num,0,sizeof(num));
        memset(exist,0,sizeof(exist));
        int m;
        cin >> m;        
        string word;
        for (int i =0;i<m;i++){
            cin >> word;
            int w1,w2;
            w1 = char_order(word[0]); 
            w2 = char_order(word[word.length()-1]);
            M[w1][w2] = 1;
            num[w1]--;
            num[w2]++;
            exist[w1]=1;
            exist[w2]=1;
        }
        vector<int> z;
        for (int i =0;i<26;i++){
            if (num[i] !=0){
                z.push_back(num[i]);
            }
        }
        if ((z.size() == 1 && abs(z[0]) > 1 ) || (z.size()==2 && (z[0]!=-z[1] || abs(z[0]) !=1)) || z.size() > 2){
            cout << "The door cannot be opened."<< endl;
        }
        else{
            if (sovle()){
                cout << "Ordering is possible." << endl;
            }
            else{
                cout << "The door cannot be opened." << endl;
            }
        }
    
    }


}
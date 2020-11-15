#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <cstring>

using namespace std;

const int MaxN=100;

int np,nt,nf;
int fire_count;
map<int,int> T[MaxN][2];
int Token[MaxN];

bool simulate(){
    fire_count = 0;
    while (fire_count < nf ){            
        int next_t = -1;
        for (int i =0;i<nt;i++){
            bool flag = true;
            for (auto item:T[i][0]){
                if (Token[item.first] < item.second){
                    flag=false;
                    break;
                }
            }
            
            if (flag){
                next_t = i;
                break;
            }
        }

        if (next_t == -1){
            return false;
        }
        
        fire_count++;
        
        for (auto input:T[next_t][0]){
            Token[input.first]  -= input.second;
        }
        for (auto output:T[next_t][1]){
            Token[output.first] += output.second;
        }
    }

    if (fire_count == nf){
        return true;
    }
    else{
        return false;
    }
}

int main()
{
    ifstream fin("input.txt");
    cin.rdbuf(fin.rdbuf());
    int case_n =0;
    while (cin >> np && np !=0){
        case_n++;
        for (int i=0;i<np;i++){
            cin >> Token[i];
        }
        cin >> nt;
        for (int i =0;i<nt;i++){
            T[i][1].clear();
            T[i][0].clear();
            int temp;
            while (cin >> temp && temp!=0){
                if (temp > 0) {
                    T[i][1][temp-1]++;
                }
                else{
                    T[i][0][-temp-1]++;
                }
            }
        }
        cin >> nf;
        
        if (simulate()){
            printf("Case %d: still live after %d transitions\n",case_n,nf);
        }
        else{
            printf("Case %d: dead after %d transitions\n",case_n,fire_count);
        }
        cout << "Places with tokens:";
        for (int i=0;i<np;i++){
            if (Token[i] > 0){
                printf(" %d (%d)",i+1,Token[i]);
            }
        }
        cout << endl << endl;
    }
}
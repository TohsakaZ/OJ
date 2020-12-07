#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

const int MaxArr=1E6;

char arr[MaxArr];

int n,L;
int count;
bool dfs(int idx){
    for (int i=0;i<L;i++){
        char now = 'A'+i; 
        arr[idx]= now;
        bool flag=true;
        for (int j=1;j<=(idx+1)/2;j++){
            if (strncmp(arr+idx-2*j+1,arr+idx-j+1,j)==0){
                flag=false;
                break;
            }
        }
        if (flag){
            count++;
            if (count==n){
                for (int k =0;k<=idx;k++) {
                    if (k!=0 && k%64==0){
                        cout << endl;
                    }
                    else if (k!=0 && k%4==0){
                        cout  << " ";
                    }
                    cout << arr[k];
                }
                cout << endl;
                cout << idx+1 << endl;
                return true;
            }
            else{
                if (dfs(idx+1)){
                    return true;
                }
            }
        }
    }
    return false;
}

int main()
{
    ifstream fin("input.txt");
    cin.rdbuf(fin.rdbuf());

    while (cin >> n >> L && n!=0 && L!=0){
        count=0;
        dfs(0);
    }

}
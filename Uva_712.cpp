#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

const int MaxN = 1<<8;
const int MaxD = 8;

int order[MaxD];
int x[MaxD];
int v[MaxN];

int main()
{
    ifstream fin("input.txt");
    cin.rdbuf(fin.rdbuf());

    int case_n=0;
    int n;
    string templine;
    while (cin >> n && n !=0){
        case_n++;
        for (int i =0;i<n;i++){
            cin >> templine;
            order[i] = templine[1]-'0';
        }
        cin >> templine;
        for (int i =0;i<templine.size();i++){
            v[i] = templine[i] - '0';
        }
        int m;
        cin >> m;
        printf("S-Tree #%d:\n",case_n);
        for (int i =0;i<m;i++){
            cin >> templine;
            for (int j =0;j<templine.size();j++){
                x[j] = templine[j] - '0';
            }
            int final = 1;
            for (int k =0;k<n;k++){
                if (x[order[k]-1]){
                    final = 2*final+1;
                }
                else{
                    final = 2*final;
                }
            }
            int total_before = (1<<n) - 1;
            cout << v[final- total_before -1];
        }
        cout << endl;
        cout << endl;
    }

}
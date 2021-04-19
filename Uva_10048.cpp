#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;
const int MaxN=101;
int V[MaxN][MaxN];
int Dist[MaxN][MaxN];
int C,S,Q;
void floyd(){
    for (int k =0;k<C;k++){
        for (int i=0;i<C;i++){
            for (int j=0;j<C;j++){
                if (Dist[i][k] > -1 && Dist[k][j] > -1){
                    if (Dist[i][j] > -1){
                        Dist[i][j] = min(Dist[i][j],max(Dist[i][k],Dist[k][j])) ;
                    }
                    else{
                        Dist[i][j] = max(Dist[i][k],Dist[k][j]);
                    }
                }
            }
        }
    }
}
void print(){
    for (int i =0;i<C;i++){
        for (int j =0;j<C;j++){
            cout << Dist[i][j] << " ";
        }
        cout << endl;
    }
}
int main(){
    int case_n=0;
    while (cin >> C >> S >> Q && (C+S+Q!=0)){
        if (case_n){
            cout << endl;
        }
        case_n++;
        memset(Dist,-1,sizeof(Dist));
        for (int i =0;i<C;i++){
            Dist[i][i] =0;
        }
        for (int i =0;i<S;i++){
            int a,b,c;
            cin >> a >> b >> c;
            a-=1;
            b-=1;
            Dist[a][b] = c;
            Dist[b][a] = c;
        }
        floyd();
        cout << "Case #" << case_n << endl;
        for (int i =0;i<Q;i++){
            int a,b;
            cin >> a >> b;
            a--;
            b--;
            if (Dist[a][b]>-1){
                cout << Dist[a][b] << endl;
            }
            else{
                cout << "no path" << endl;
            }

        }
    }
    
}
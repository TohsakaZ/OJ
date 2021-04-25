#include <iostream>
#include <fstream>

using namespace std;

int64_t n,m;
int N,S,W,E;


int main(){
    ifstream fin("input.txt");
    cin.rdbuf(fin.rdbuf());
    int case_i=0;
    while (cin >> n >> m && n && m){
        case_i++;
        cin >> N >> S >> W >> E;
        int64_t ans = 0;
        int r_move,c_move;
        int r_left,c_left;
        if (N==S){
            r_left =0;
        }
        else{
            r_left = max(N,S) - min(N,S) -1;
        }
        r_move = N+S - r_left;
        if (W==E){
            c_left=0;
        }
        else{
            c_left = max(W,E) - min(W,E) - 1;
        }
        c_move = W+E-c_left;
        // First
        int64_t rr = m;
        int64_t cc = n; 
        if (r_move && c_move && rr > 1 && cc > 1){
            int64_t v1=(r_move-1)*(n*m-m)+(n*m) + (c_move-1)*(n*m-m-n+1)+(n*m-m);
            int64_t v2 = (c_move-1)*(n*m-n)+(n*m) + (r_move-1)*(n*m-m-n+1)+(n*m-n);
            ans = max(v1,v2);
            rr--;
            cc--;
        }
        else if (r_move && cc > 1){
            ans = (r_move-1)*(n*m-m)+(n*m);
            cc--;
        }
        else if (c_move && rr > 1){
            ans = (c_move-1)*(n*m-n)+(n*m);
            rr--;
        }
        if (cc== 1){
            r_left = min(1,N+S);
        }
        if (rr == 1){
            c_left = min(1,W+E);
        }
        // Second
        while (r_left && c_left && rr && cc){
            ans += rr*cc;
            if (rr < cc){
                cc--;
                r_left--;
            }
            else{
                rr--;
                c_left--;
            }
        }
        while (r_left && rr && cc){
            ans += rr*cc;
            cc--; 
            r_left--;
        }
        while (c_left && rr && cc){
            ans +=  rr*cc;
            rr--;
            c_left--; 
        }
        printf("Case %d: %lld\n",case_i,ans);
    }
}

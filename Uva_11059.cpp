#include <iostream>
#include <fstream>

using namespace std;

const int MaxN=20;
int arr[MaxN];

int main(){
    ifstream fin("input.txt");
    cin.rdbuf(fin.rdbuf());
    
    int N;
    int64_t ans=0;
    int case_i=0;
    while (cin >> N)
    {
        ans =0;
        case_i++;
        for (int i =0;i<N;i++){
            cin >> arr[i];            
        }
        for (int i =0;i<N;i++){
            int64_t dot = 1;
            for (int j =i;j<N;j++){
                dot *= arr[j]; 
                ans = max(ans,dot);
            }
        }
        printf("Case #%d: The maximum product is %ld.\n\n",case_i,ans);
    }
}
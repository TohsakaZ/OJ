#include <iostream>
#include <fstream>

using namespace std;

int main(){
    ifstream fin("input.txt");
    cin.rdbuf(fin.rdbuf());

    int64_t ans;
    int case_n;
    cin >> case_n;
    for (int case_i = 0; case_i < case_n;case_i++){
        ans = 0;
        int64_t  n, s1, v1, s2, v2;
        cin >> n >> s1 >> v1 >> s2 >> v2;
        if (s1 * s2 < n){
            int64_t value = max(s2 * v1, s1 * v2);
            ans += (n / (s1 * s2)) * value;
            n = n % (s1 * s2);
        }
        
        if (s2>s1){
            swap(s1, s2);
            swap(v1, v2);
        }

        int64_t result=0;
        for (int i = 0; i <= (n / s1); i++)
        {
            result = max(i * v1 + (n - i * s1) / s2 * v2, result);
        }
        printf("Case #%d: %lld\n", case_i + 1, result + ans);
    }
}
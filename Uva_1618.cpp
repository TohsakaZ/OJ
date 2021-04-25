#include <iostream>
#include <fstream>

using namespace std;

const int MaxN = 5000;
int n;
int arr[MaxN];
int brr[MaxN];

bool find_ans(int* a)
{
    for (int a1=0;a1<n-3;a1++){
        int  last_a2 = 0;
        for (int a2=a1+1;a2<n-2;a2++){
            if (a[a2] <= a[a1]  || a[a2] <= last_a2){
                continue;
            }
            int last_a3=INT32_MAX;
            for (int a3 = a2+1;a3<n-1;a3++){
                if (a[a3] >= a[a1] || a[a3] >= last_a3){
                    continue;
                }
                for (int a4 = a3+1;a4<n;a4++){
                    if (a[a4] >= a[a2] || a[a4] <= a[a1]){
                        continue;
                    }
                    return true;
                }
                last_a3 = a[a3];
            }
            last_a2 = a[a2];
        }
    }
    return false;
}

int main()
{
    ifstream fin("input.txt");
    cin.rdbuf(fin.rdbuf());
    int case_n;
    cin >> case_n;
    for  (int case_i=0;case_i<case_n;case_i++){
        cin >> n;
        for (int i =0;i<n;i++){
            cin >> arr[i];
            brr[n-i-1] = arr[i];
        }
        if (find_ans(arr) || find_ans(brr)){
            cout << "YES" << endl;
        }
        else{
            cout << "NO" << endl;
        }
    }
}
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;


class point
{
public:
    int x,y;
};

int n;
const int MaxN =100000;
point arr[MaxN];

int main()
{
    ifstream fin("input.txt");
    cin.rdbuf(fin.rdbuf());

    int case_n;
    cin >> case_n;
    for (int i =0;i<case_n;i++){
        cin >> n;
        for (int i =0;i<n;i++){
            cin >> arr[i].x >> arr[i].y;
        }
        sort(arr,arr+n,[](point l,point r)->bool{return l.y < r.y || (l.y == r.y && l.x < r.x);});

        int cnt = arr[0].y;
        int ans =0;
        for (int i=1;i<n;i++){
            if (arr[i].x > cnt){
                ans++;
                cnt = arr[i].y;
            }
            else{
                if (cnt == arr[i].y) {
                    continue;
                }
                else{
                    cnt++;
                }
            }
        }
        cout << ans << endl;;
    }

}
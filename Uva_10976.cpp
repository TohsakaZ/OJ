#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main()
{
    ifstream fin("input.txt");
    cin.rdbuf(fin.rdbuf());
    int k;
    while (cin >> k){
        vector<pair<int64_t,int64_t> > ans;
        for (int64_t y=k+1;y<=2*k;y++){
            if (k*y % (y-k) == 0){
                int64_t x = k*y / (y-k);
                ans.push_back(make_pair(x,y)); 
            }
        }
        cout << ans.size() << endl;
        for (auto item :ans){
            printf("1/%d = 1/%ld + 1/%ld\n",k,item.first,item.second);
        }
    }
}
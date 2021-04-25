#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <cstring>
#include <algorithm>

using namespace std;

class dd
{
public:
    int id_day;
    int id_order; 

    bool operator<(const dd& other) const
    {
        return this->id_day < other.id_day;
    }

    static int cnt;
};

int dd::cnt =0;
const  int MaxN=1000010;
int n,m;
int last[MaxN];
int dragon[MaxN];

int main()
{
    ifstream fin("input.txt");
    cin.rdbuf(fin.rdbuf());

    memset(dragon,0,sizeof(int)*dd::cnt);
    int case_n;
    cin >> case_n; 
    for  (int case_i=0;case_i<case_n;case_i++)
    {
        memset(dragon,0,sizeof(int)*dd::cnt);
        dd::cnt = 0;
        cin >> n >> m;
        //vector<dd> dday;
        set<dd> dday;
        memset(last,-1,sizeof(int)*(n+1));
        bool flag = true;
        for (int i=0;i<m;i++)
        {
            int rain;
            cin >> rain;
            if (!flag){
                continue;
            }
            if (rain==0){
                dd new_dd;
                new_dd.id_day = i;
                new_dd.id_order = dd::cnt++;
                dday.insert(new_dd);
            }
            else{
                dd key_dd;
                key_dd.id_day = last[rain];
                auto find_iter = dday.lower_bound(key_dd);
                if (find_iter == dday.end()){
                    flag = false;
                    continue;
                }
                dragon[find_iter->id_order] = rain;
                last[rain] = i;
                dday.erase(find_iter);
            }
        }

        if (!flag){
            cout << "NO" << endl;
        }
        else{
            cout << "YES" << endl;
            for (int i =0;i<dd::cnt;i++){
                if (i){
                    cout  << " ";
                }
                cout  << dragon[i];
            }
            cout << endl;
        }
    }

}
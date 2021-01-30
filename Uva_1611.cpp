#include <iostream>
#include <fstream>
#include <vector>
#include <map>

using namespace std;

void print(vector<int> & orig){
    for (int i = 0; i < orig.size();i++){
        cout << orig[i]+1 << " ";
    }
    cout << endl;
}


void swap(int beg,int end,vector<int>& loc,vector<int>& orig){
    int num = (end-beg+1) / 2;
    for (int i = beg; i <beg+num; i++)
    {
        int temp;
        temp = orig[i];
        orig[i] = orig[i + num];
        loc[orig[i]] = i;
        orig[i + num] = temp;
        loc[orig[i + num]] = i + num;
    }
    //print(orig);
}
int main()
{
    ifstream fin("input.txt");
    cin.rdbuf(fin.rdbuf());
    int case_n;
    cin >> case_n;
    for (int i = 0; i < case_n;i++){
        int n;
        cin >> n;
        vector<int> arr(n,0);
        vector<int> orig;
        for (int i = 0; i < n; i++)
        {
            int temp;
            cin >> temp;
            arr[temp-1] = i;
            orig.push_back(temp - 1);
        }
        vector<pair<int, int> > ans;
        for (int i =0;i<n;i++){
            if (arr[i] == i){
                continue;
            }
            int loc = arr[i];
            if (2*loc - i - 1 < n){
                ans.push_back(make_pair(i + 1, 2 * loc - i));
                swap(i, 2 * loc - i - 1, arr,orig);
            }
            else{
                int beg = (loc - i) % 2 ? i : i + 1;
                ans.push_back(make_pair(beg+1,loc+1));
                swap(beg, loc,arr,orig);
                loc = arr[i];
                ans.push_back(make_pair(i + 1, 2 * loc - i));
                swap(i, 2 * loc - i - 1, arr,orig);
            }
        }
        cout << ans.size() << endl;
        for (auto item : ans){
            cout << item.first << " " << item.second << endl;
        }
    }
}
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void move_head_pre(vector<int>& ans,int n,int& head,int& last_loc){
    head = (head - 1 + n) % n;
    ans.push_back(2);
    if (last_loc ==-1){
        last_loc = ans.size()-1;
    }
    if (ans.size() - last_loc == n){
        ans.erase(ans.begin() + last_loc, ans.end());
    }
}


int main()
{
    ifstream fin("input.txt");
    cin.rdbuf(fin.rdbuf());

    int n;
    while (cin >> n && n !=0){
        vector<int> arr;
        for (int i = 0; i < n; i++)
        {
            int temp;
            cin >> temp;
            arr.push_back(temp);
        }

        //for (int i = 0;i<arr.size();i++){
            //cout << arr[i] << " ";
        //}
        //cout << endl;
        vector<int> ans;
        int head = 0;
        int last_loc = -1;
        for (int i = 0; i < n - 1; i++)
        {
            while (head !=n-2){
                move_head_pre(ans, n, head,last_loc);
            }
            while (head >=i && head !=n-1){
                if (arr[head] > arr[head+1])
                {
                    swap(arr[head], arr[head+1]);
                    ans.push_back(1);
                    last_loc = -1;
                }
                move_head_pre(ans, n, head,last_loc);
            }
        }
        while (head !=0){
            move_head_pre(ans, n, head,last_loc);
        }
        //for (int i = 0;i<arr.size();i++){
        //    cout << arr[i] << " ";
        //}
        //cout << endl;
        for (int i = ans.size(); i > 0; i--)
        {
            cout << ans[i - 1];
            if (ans[i-1]==1){
                swap(arr[0], arr[1]);
            }
            else{
                arr.insert(arr.end(), arr[0]);
                arr.erase(arr.begin());
            }
        }
        cout << endl;
        //for (int i = 0;i<arr.size();i++){
        //    cout << arr[i] << " ";
        //}
        //cout << endl;
    }
}
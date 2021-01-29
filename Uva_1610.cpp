#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;


void add_last(string& orig,string& temp,int loc){
    if (loc < orig.length()-1){
        if (orig[loc]=='Z'){
            temp += orig[loc];
            add_last(orig, temp, loc + 1);
        }
        else{
            temp += orig[loc]+1;
        }
    }
    else {
        temp += orig[loc];
    }
}

int main()
{
    ifstream fin("input.txt");
    cin.rdbuf(fin.rdbuf());

    int n;
    while (cin >> n && n!=0){
        vector<string> arr;
        for (int i =0;i<n;i++){
            string templine;
            cin >> templine;
            arr.push_back(templine);
        }

        sort(arr.begin(), arr.end());
        string t1 = arr[n / 2 - 1];
        string t2 = arr[n / 2];
        int loc = 0;
        string ans;
        while (loc < t1.length() && t1[loc] == t2[loc])
        {
            ans += t1[loc];
            loc++;
        }

        if (loc < t1.length()){
            add_last(t1, ans, loc);
            if (ans == t2)
            {
                ans = t1.substr(0, loc + 1);
                add_last(t1, ans, loc + 1);
            }
        }
        cout << ans << endl;
    }
}
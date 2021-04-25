#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

int L, D, n;

void cal_range(int x,int y,double& x1,double& x2){
    double temp = sqrt((double)D * (double)D - (double)y * (double)y);
    x1 = x - temp;
    x2 = x + temp;
    if (x1<0.0){
        x1=0.0;
    }
    if (x2>(double)L){
        x2 = (double)L; 
    }
    return ;
}

int  main()
{
    ifstream fin("input.txt");
    cin.rdbuf(fin.rdbuf());

    while (cin >>L)
    {
        cin >> D;
        cin >> n;
        vector<pair<int, int>> arr;
        for (int i = 0;i<n;i++){
            int x, y;
            cin >> x >> y;
            arr.push_back(make_pair(x, y));
        }
        sort(arr.begin(), arr.end(), [](pair<int, int> x, pair<int, int> y) -> bool { return x.first < y.first; });
        double x1,x2;            
        cal_range(arr.begin()->first,arr.begin()->second,x1,x2);
        int count =1;
        for (auto& item: arr){
            double l,r;  
            cal_range(item.first,item.second,l,r);
            if (l > x2){
                count++;
                x1 = l;
                x2 = r;
            }
            else{
                x1 = max(x1,l);
                x2 = min(x2,r);
            }
        }
        cout << count  << endl;
    }
}

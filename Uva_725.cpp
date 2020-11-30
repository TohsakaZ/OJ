#include <iostream>
#include <fstream>
#include <set>
#include <vector>

using namespace std;

vector<int> ans;
int a[5],N;
set<int> table;

void div(int idx){
    if (idx == 5){
        int div_num=0;
        for (int i =0;i<5;i++){
            div_num = 10*div_num + a[i];
        }
        int other = N * div_num;
        int count=0;
        bool flag=true;
        while (count<5){
            int temp = other%10;
            if (table.count(temp)!=0){
                flag =false;
                break;
            }
            table.insert(temp);
            other = other /10;
            count++;
        }
        if (other!=0 ){
            flag=false;
        }
        if (flag){
            ans.push_back(div_num);
        }
        table.clear();
        for (int i =0;i<5;i++){
            table.insert(a[i]);
        }
        return;
    }
    for (int i =0;i<10;i++){
        if (table.count(i)!=0){
            continue;
        }
        a[idx] = i;
        table.insert(i);
        div(idx+1);
        table.erase(i);
    }
}


int main()
{
    ifstream fin("input.txt");
    cin.rdbuf(fin.rdbuf());

    bool first=true;
    while (cin >> N && N !=0){
        if (first){
            first =false;
        }
        else{
            cout  <<endl;
        }
        ans.clear();
        table.clear();
        div(0);
        if (ans.size()==0){
            printf("There are no solutions for %d.\n",N);
        }
        else{
            for (int j=0;j<ans.size();j++){
                printf("%05d / %05d = %d\n",ans[j]*N,ans[j],N);
            }
        }
    }
}
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <set>


using namespace std;

map<int,int> decode_set(string& set,map<string,int>& talbe_index,vector<string>& table)
{
    map<int,int> result;
    set=set.substr(1);
    set[set.length()-1]=',';
    int idx=0;
    while (set.find(',',idx)!=string::npos && set.find(":",idx)!=string::npos)
    {
        int cola_idx=set.find(':',idx);
        int comma_idx=set.find(',',idx);
        string str1 = set.substr(idx,cola_idx-idx);
        string str2 = set.substr(cola_idx+1,comma_idx-cola_idx-1);
        if (talbe_index.count(str1)==0){
            talbe_index[str1]=table.size();
            table.push_back(str1);
        }
        if (talbe_index.count(str2)==0){
            talbe_index[str2]=table.size();
            table.push_back(str2);
        }
        result[talbe_index[str1]]=talbe_index[str2];
        idx = comma_idx + 1;
    }

    return result ;
}

void cout_set(set<string>& sets,char mark)
{
    if (sets.size()!=0){
        for (auto item:sets){
            if (item==*sets.begin()){
                cout << mark;
            }
            else{
                cout << ',';
            }
            cout << item;
        }
        cout << endl;
    }
}

int main()
{
    //ifstream fin;
    //fin.open("input.txt");
    //cin.rdbuf(fin.rdbuf());

    int test_nubmer=0;
    string empty;
    cin >> test_nubmer;
    getline(cin, empty);
    while (test_nubmer--)
    {
        string str_set1,str_set2;
        getline(cin,str_set1);
        getline(cin,str_set2);        

        vector<string> table;
        map<string,int> table_index;
        auto set1 = decode_set(str_set1,table_index,table);
        auto set2 = decode_set(str_set2,table_index,table);

        set<string> add;
        set<string> remove;
        set<string> v_change;
        for (const auto& item: set2)
        {
            if (set1.count(item.first)==0){
                add.insert(table[item.first]);    
            }
            else{
                if (item.second!=set1[item.first]){
                    v_change.insert(table[item.first]);
                }
            } 
        }

        for (const auto& item : set1)
        {
            if (set2.count(item.first)==0){
                remove.insert(table[item.first]);
            }
        }

        if (add.size()==0 && remove.size()==0 && v_change.size()==0){
            cout << "No changes"<< endl;
        } 
        else{
            cout_set(add,'+'); 
            cout_set(remove,'-'); 
            cout_set(v_change,'*'); 
        }

        cout << endl;
    }
   }
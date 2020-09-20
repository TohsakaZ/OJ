/*
这题主要涉及了字典数(trie tree) 和 斐波那契数列的求解
字典数这边看了相关AC代码基本就是数组实现或者链表实现
斐波那契数列主要就是大数相加（其他代码的加速部分就是 不计算50位以后的加减了，但是这个感觉没有特别严格的数学证明，所以也不太确定）
*/
#include <iostream>
#include <climits>
#include <time.h>
#include <fstream>
#include <map>
#include <set>
#include <vector>

using namespace std;

int trie_table[100000][10];
int value_table[100000];
int trie_count=0;

void insert_trie_table(const vector<int>& number_list,int number){
    int pos=0;
    for (int i =0;i<number_list.size();i++){
        if (trie_table[pos][number_list[i]]==0){
            trie_table[pos][number_list[i]]=++trie_count;
        }
        pos = trie_table[pos][number_list[i]];
        if (value_table[pos]==0){
            value_table[pos] = number;
        }
    }
}


int find_trie_table(const string& str_nubmer){
    int pos=0;
    for (int i =0;i<str_nubmer.size();i++){
        int k = str_nubmer[i]- '0';
        if (trie_table[pos][k] == 0){
            return -1;
        }
        pos = trie_table[pos][k];
    }
    return value_table[pos];
}



class number_table{
public:
    number_table(){};
    number_table(int index,int small_number):
        index(index),
        small_number(small_number)
    {
    }
    map<int,number_table> k;
    int index;
    int small_number;
};

number_table table_list(0,0);

void insert_table(const vector<int>& number_list,int number){
    auto* table = &table_list;
    for (int i =0;i<number_list.size();i++){
        if (table->k.count(number_list[i]) ==0){
            table->k[number_list[i]]=number_table(table->index+1,number);
        }
        table = &table->k[number_list[i]];
    }
}

int find_table(string& str_number){
    auto* table = &table_list;
    for (int i =0;i<str_number.length();i++){
        int k = str_number[i] - '0';
        if (table->k.count(k)==0){
            return -1;
        } 
        table = & table->k[k];
    }
    return table->small_number; 
}

class big_int
{
public:
    big_int(){
    }
    big_int(const string& str_number){
        for (auto str_iter=str_number.rbegin();str_iter!=str_number.rend();str_iter++){
            num.push_back(*str_iter - '0');
        }
    }
    vector<int> num;

    big_int operator+(const big_int& Other) 
    {
        big_int ans;
        int common_size = min(num.size(),Other.num.size());
        int add =0;
        for (int i =0;i<common_size;i++){
            int k  = num[i] + Other.num[i] + add;
            ans.num.push_back(k % 10);
            add = k / 10; 
        }
        auto & left = num;
        if (num.size() == common_size){
            auto& left = Other.num;
        }
        int left_size = left.size();
        for (int i=common_size;i< left_size;i++){
            int k = left[i]+add;
            ans.num.push_back(k%10);
            add = k/10;
        } 
        if (add !=0){
            ans.num.push_back(add);
        }
        return ans; 
    }

    vector<int> get_front_number(){
        vector<int> ans;
        for (int i =0; i<40 && i<num.size();i++){
            ans.push_back(num[num.size()-1-i]);
        }
        return ans;
    }

    void print(){
        for (auto num_iter = num.rbegin();num_iter!=num.rend();num_iter++){
            cout << *num_iter;
        }
        cout << endl;
    }
};

void fibonacci(int num){
    big_int a("1");
    big_int b("1");
    insert_table(vector<int>(1,1),0);
    for (int i =2;i<num;i++){
        big_int temp = a;
        a = a+b;
        b = temp;
        insert_table(a.get_front_number(),i);
    }
}

int main()
{
    fibonacci(100000);
    //ifstream fin("input.txt");
    //cin.rdbuf(fin.rdbuf());

    int case_nubmer=0;
    cin >> case_nubmer;
    for (int i=0;i<case_nubmer;i++){
        string prefix_num;
        cin >> prefix_num;
        cout << "Case #"<< i+1 << ": " << find_table(prefix_num) << endl;
    }
}
#include <vector>
#include <map>
#include <set>
#include <bitset>
#include <math.h>
#include <iostream>
#include <iomanip>
#include <cstring>

using namespace std;

int num_count(int k,int size){
    int ans=0;
    while (size--){
        if (k&1){
            ans++;
        }
        k = k >> 1;
    }
    return ans;
}

int B2D(string s){
    for (int i=0;)
}

const int size_num = 7;

int main()
{
    int Max_site =11;
    int k[Max_site] = {
        (int)bitset<size_num>("1111000").to_ulong(),
        (int)bitset<size_num>("1101100").to_ulong(),
        (int)bitset<size_num>("1111101").to_ulong(),
        (int)bitset<size_num>("1101101").to_ulong(),
        (int)bitset<size_num>("1101111").to_ulong(),
        (int)bitset<size_num>("1111111").to_ulong(),
        (int)bitset<size_num>("1101111").to_ulong(),
        (int)bitset<size_num>("1101100").to_ulong(),
        (int)bitset<size_num>("1101101").to_ulong(),
        (int)bitset<size_num>("1111100").to_ulong(),
        (int)bitset<size_num>("1101000").to_ulong()
    };

    int site_ans[Max_site+1];
    int sat_ans[Max_site+1];
    memset(sat_ans,0,sizeof(sat_ans));
    for (int site_select=1;site_select<=(1<<(Max_site+1)-1);site_select++)
    {
        int j = Max_site;
        int site_num = 0;
        int sat_num=(1<<size_num)-1;
        int temp_site = site_select;
        while (j--){
            if (temp_site&1){
                site_num++; 
                sat_num=k[j] & sat_num;
            }
            temp_site = temp_site>>1;
        }
        if (num_count(sat_num,size_num) > sat_ans[site_num]){
            sat_ans[site_num]=num_count(sat_num,size_num); 
            site_ans[site_num]=site_select;
        }
    }
    double  ratio=0.7;
    int num_beg = Max_site*ratio;
    for (int num=num_beg+1;num<=Max_site;num++){
        if (sat_ans[num] < sat_ans[num-1]) {
            cout << num-1 <<" " << site_ans[num-1] << " " << sat_ans[num-1] << endl;
            break;
        }
    }

}
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stack>
#include <cstring>

using namespace std;
struct node 
{
    node(int link,int mb,int pb,int number):link(link),middle_beg(mb),post_beg(pb),number(number)
    {}
    int link;
    int middle_beg;
    int post_beg;
    int number;
};

const int MaxN = 10010;
int l[MaxN];
int r[MaxN];
int v[MaxN];
int top=0;

int find_vector(vector<int>& v,int beg,int end,int ans){
    for (int i = beg;i<=end;i++){
        if (v[i] == ans){
            return i;
        }
    }
}

void inorder(int head){
    if (head ==-1){
        return;
    }
    inorder(l[head]);
    cout << v[head] << " ";
    inorder(r[head]);
}

void postorder(int head){
    if (head == -1){
        return; 
    }
    postorder(l[head]);
    postorder(r[head]);
    cout << v[head] <<" ";
}

pair<int,int> value(int head){
    if (head == -1){
        return make_pair(INT32_MAX,INT32_MAX);
    }
    // left node
    if (l[head] == -1 && r[head] == -1){
        return make_pair(v[head],v[head]); 
    }
    else{
        auto l_result = value(l[head]);
        auto r_result = value(r[head]);
        auto min_reuslt = min(l_result,r_result); 
        return make_pair(min_reuslt.first+v[head],min_reuslt.second);
    } 
    
}


int value_no_rescure(){
    stack<pair<int,int> > s;
    s.push(make_pair(0,0));
    int sum=INT32_MAX;
    int best_ans = -1;
    while (!s.empty()){
        int head = s.top().first;
        int sum = s.top().second;
        s.pop();
        sum += v[head];
        // TODO:
    }

}


int main()
{
    ifstream fin("input.txt");
    cin.rdbuf(fin.rdbuf());

    string templine1,templine2;
    while (getline(cin,templine1) && getline(cin,templine2)){
        vector<int> middle,post;;
        top = 0;
        memset(l,-1,sizeof(l));
        memset(r,-1,sizeof(r));
        memset(v,-1,sizeof(v));
        stringstream temp_split1(templine1),temp_split2(templine2);
        int k;
        while (temp_split1 >> k) middle.push_back(k);
        while (temp_split2 >> k) post.push_back(k);
        
        stack<node> s;
        s.push(node(0,0,0,middle.size()));
        while (!s.empty()){
            node n=s.top(); 
            s.pop();
            v[n.link] =post[n.post_beg+n.number-1];
            int find_loc = find_vector(middle,n.middle_beg,n.middle_beg+n.number-1,v[n.link]);
            int left_size = find_loc - n.middle_beg;
            int right_size = n.middle_beg+n.number-1-find_loc;
            // add left node
            if (left_size!=0){
                l[n.link]=++top;  
                s.push(node(l[n.link],n.middle_beg,n.post_beg,left_size));
            }
            // add right node
            if (right_size!=0){
                r[n.link]=++top;
                s.push(node(r[n.link],find_loc+1,n.post_beg+left_size,right_size));
            }
        }             

        cout << value(0).second << endl;
        
        //inorder(0);
        //cout << endl;
        //postorder(0);
        //cout << endl;
    }
    
    


    
}

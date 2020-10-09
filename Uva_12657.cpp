#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

class node{
public:
    int next;
    int pre;
    static bool direction;
    int right() const{
        return node::direction?next:pre;
    }
    int left() const{
        return node::direction?pre:next;
    }

    void right(int value) {
        if (direction){
            next = value;
        }
        else{
            pre = value;
        }
    }

    void left(int value){
        if (direction){
            pre = value;
        }
        else{
            next = value;
        }
    }
};

bool node::direction=true;

const int Max_N = 100000;
node node_list[Max_N+10];

void print(node* list,int head,int tail){
    int now;
    if (node::direction){
        now = head;
    }
    else{
        now = tail;
    }
    for (now=list[now].right();list[now].right()!=-1;now=list[now].right()){
        printf("%d ",now);
    }
    cout << endl;
}

int main()
{
    //ifstream fin("input.txt");
    //cin.rdbuf(fin.rdbuf());
    int n,m;
    int case_i=0;
    while (cin >> n >> m){
        node::direction = true;
        case_i ++;
        //init
        int head = 0;
        int tail = n+1;
        node_list[head].right(1);
        node_list[head].left(-1);
        node_list[tail].left(n);
        node_list[tail].right(-1); 
        for (int i =1;i<=n;i++){
            node_list[i].next = i+1;
            node_list[i].pre = i-1;
        }
        //print(node_list,head,tail);
        for (int i =0;i<m;i++){
            int a,b,c;
            cin >> a;
            if (a!=4){
                cin >> b >> c;
            }
        
            if (a==1){
                if (node_list[c].left() ==b ){
                    continue;
                }
                // remove X
                node_list[node_list[b].right()].left(node_list[b].left());
                node_list[node_list[b].left()].right(node_list[b].right());

                // ADD X in Y left
                node_list[b].left(node_list[c].left());
                node_list[b].right(c);
                node_list[node_list[c].left()].right(b);
                node_list[c].left(b);
            }
            else if (a==2){

                if (node_list[c].right() == b){
                    continue;
                }
                // remove X
                node_list[node_list[b].right()].left(node_list[b].left());
                node_list[node_list[b].left()].right(node_list[b].right());
                // ADD X in Y RIGHT
                node_list[b].left(c);
                node_list[b].right(node_list[c].right());
                node_list[node_list[c].right()].left(b);
                node_list[c].right(b);
            }
            else if (a==3){
                node tempnode = node_list[b]; 
                if  (node_list[b].right() == c){
                    node_list[b].left(c);
                    node_list[b].right(node_list[c].right());
                    node_list[node_list[c].right()].left(b);

                    node_list[c].right(b);
                    node_list[c].left(tempnode.left());
                    node_list[tempnode.left()].right(c);
                }
                else if (node_list[b].left() == c){
                    node_list[b].right(c);
                    node_list[b].left(node_list[c].left());
                    node_list[node_list[c].left()].right(b);

                    node_list[c].left(b);
                    node_list[c].right(tempnode.right());
                    node_list[tempnode.right()].left(c);
                }
                else{
                    // move b
                    node_list[node_list[c].left()].right(b);
                    node_list[node_list[c].right()].left(b);
                    node_list[b].left(node_list[c].left());
                    node_list[b].right(node_list[c].right());

                    node_list[tempnode.left()].right(c);
                    node_list[tempnode.right()].left(c);
                    node_list[c].left(tempnode.left());
                    node_list[c].right(tempnode.right());

                } 
            }
            else if (a==4){
                node::direction = !node::direction;
            }
            //print(node_list,head,tail);
        }
        int now = 0;
        if (node::direction){
            now = head;
        }
        else{
            now = tail;
        }
        int cnt=0;
        long sum=0;
        for (now = node_list[now].right();node_list[now].right()!=-1;now=node_list[now].right()){
            cnt++; 
            if (cnt % 2==1){
                sum += now;
            }
        }
        printf("Case %d: %ld\n",case_i,sum);
    }
}
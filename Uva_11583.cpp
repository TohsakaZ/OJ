#include <iostream>
#include <fstream>
#include <cstring>
#include <queue>
#include <stack>
#include <math.h>

using namespace std;

class circle
{
public:
    circle():x(0),y(0),r(0){};
    circle(double x,double y,double r):x(x),y(y),r(r)
    {
    };
    
    double x,y,r;

    bool get_top(){
        return y+r > 1000.0;
    }

    bool get_bottom(){
        return y-r < 0.0;
    }

    double get_left(){
        return x-r < 0.0 ? y-sqrt(r*r - x*x)  :-1;
    }

    double get_right(){
        return x+r > 1000.0 ? y - sqrt(r*r - (1000.0-x)*(1000.0-x)) :-1;
    }
};


bool circle_cross(circle& r1,circle& r2){
    double dx = r1.x-r2.x;
    double dy = r1.y-r2.y;
    return  dx*dx+dy*dy < (r1.r+r2.r) * (r1.r+r2.r);
}

circle rlist[1010];
int v[1010];
double by,ey;
int n;

bool dfs(int now){
    v[now] = 1;
    if (rlist[now].get_bottom()){
        return true;
    }
    for (int j=0;j<n;j++){
        if (v[j] == 0 && circle_cross(rlist[now],rlist[j]) && dfs(j)){          
            return true;
        }
    }

    // judge left and right
    // 这里忘记给成double导致一直卡，需要主要题目所给的数据类型
    double left = rlist[now].get_left();
    double right = rlist[now].get_right();
    if (left >=0 && left < by){
        by = left;
    }
    if (right >=0 && right < ey){
        ey = right;
    }


    return false;
}

bool ans(){
    for (int i = 0;i<n;i++){
        if (rlist[i].get_top() && dfs(i)){
            return true;
        }
    }
    return false;
}

int main()
{
    ifstream fin("input.txt");
    cin.rdbuf(fin.rdbuf());

    while (cin >> n){
        memset(v,0,sizeof(v));
        by = ey = 1000; 
        for (int i =0;i <n;i++){
            double x,y,r;
            cin >> x >> y >> r;
            rlist[i] = circle(x,y,r); 
        }
        if (!ans()){
            printf("%.2lf %.2lf %.2lf %.2lf\n",0.0,by,1000.0,ey);
        }
        else{
            cout << "IMPOSSIBLE" << endl;
        }
    }
}
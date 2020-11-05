#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <set>
#include <stack>
#include <cstring>

using namespace std;

int M[101][101][101];

int dir[6][3] = {
    {1, 0, 0},
    {-1, 0, 0},
    {0, 1, 0},
    {0, -1, 0},
    {0, 0, 1},
    {0, 0, -1}
};

class point 
{
public:
    point(int x, int y, int z) : x(x), y(y), z(z){};

    bool valid(int max_x,int max_y,int max_z){
        if ( x >=0 && x <max_x && y>=0 && y<max_y && z >=0 && z<max_z){
            return true;
        }
        else{
            return false;
        }
    }
    int x, y, z;
};


class box
{
public:
    box(){};
    void read(){
        cin >> x0 >> y0 >> z0 >> x >> y >> z;
    }
    int x0, y0, z0, x, y,z ;
};

class crd
{
public:
    crd(){};
    void add_crd(int crd){
        coord.insert(crd);
    }

    void add_min_max(){
        if (!coord.empty()){
            int min = *coord.begin() - 1;
            int max = *coord.rbegin() + 1;
            coord.insert(min);
            coord.insert(max);
        }
        coord_find = vector<int>(coord.begin(), coord.end());
        for (int i = 1; i < coord_find.size();i++){
            len.push_back(coord_find[i] - coord_find[i - 1]);
        }
    }

    int find_loc(int v){
        return lower_bound(coord_find.begin(), coord_find.end(), v) - coord_find.begin();
    }

    int number(){
        return coord.size() - 1;
    }

    int length(int len_idx){
        return len[len_idx];
    }

    int length(){
        return max_crd() - min_crd();
    }
    
    int min_crd(){
        return *coord.begin();
    }

    int max_crd(){
        return *coord.rbegin();
    }

    set<int> coord;
    vector<int> coord_find;
    vector<int> len;
};

void fill_box(box& b,crd& x_crd,crd& y_crd,crd& z_crd){
    int x_beg = x_crd.find_loc(b.x0), x_end = x_crd.find_loc(b.x0 + b.x);
    int y_beg = y_crd.find_loc(b.y0), y_end = y_crd.find_loc(b.y0 + b.y);
    int z_beg = z_crd.find_loc(b.z0), z_end = z_crd.find_loc(b.z0 + b.z);

    for (int x = x_beg; x < x_end;x++){
        for (int y = y_beg; y < y_end;y++){
            for (int z = z_beg; z < z_end;z++){
                M[x][y][z] = -1;
            }
        }
    }
}

int compute_area(int dir,point now,crd& x_crd,crd& y_crd,crd& z_crd)
{
    int x_len = x_crd.length(now.x), y_len = y_crd.length(now.y), z_len = z_crd.length(now.z);

    // xyz
    if (dir < 0){
        return x_len * y_len * z_len;
    }
    // x
    else if (dir <=1 ) {
        return y_len * z_len;
    }
    // y
    else if (dir <=3){
        return x_len * z_len;
    }
    // z
    else{
        return x_len * y_len;
    }
}

pair<int,int> dfs(point beg,crd& x_crd,crd& y_crd,crd& z_crd)
{
    int total_area = 0;
    int total_volume = 0;
    stack<point> s;
    s.push(beg);
    M[beg.x][beg.y][beg.z] = 1;
    while (!s.empty())
    {
        point p = s.top();
        s.pop();
        total_volume += compute_area(-1, p, x_crd, y_crd, z_crd);
        for (int d = 0; d < 6; d++)
        {
            point next(p.x + dir[d][0], p.y + dir[d][1], p.z + dir[d][2]);
            if (next.valid(x_crd.number(),y_crd.number(),z_crd.number())){
                if (M[next.x][next.y][next.z] == -1){
                    // compute area
                    total_area += compute_area(d, next, x_crd, y_crd, z_crd);
                }
                else if (M[next.x][next.y][next.z] == 0){
                    M[next.x][next.y][next.z] = 1;
                    s.push(next);
                }
            }
        }
    }

    return make_pair(total_area, total_volume);
}

int main()
{
    ifstream fin("input.txt");
    cin.rdbuf(fin.rdbuf());

    int case_n;
    cin >> case_n;
    while (case_n--){
        // init value;
        crd x_crd, y_crd, z_crd;
        memset(M, 0, sizeof(M));

        int box_n;
        cin >> box_n;
        vector<box> box_list;
        // read all box info
        for (int i = 0; i < box_n;i++){
            box new_box;
            new_box.read();
            
            x_crd.add_crd(new_box.x0);
            x_crd.add_crd(new_box.x0 + new_box.x);

            y_crd.add_crd(new_box.y0);
            y_crd.add_crd(new_box.y0 + new_box.y);

            z_crd.add_crd(new_box.z0);
            z_crd.add_crd(new_box.z0 + new_box.z);

            box_list.push_back(new_box);
        }
        x_crd.add_min_max();
        y_crd.add_min_max();
        z_crd.add_min_max();

        for (int i = 0; i < box_n;i++){
            fill_box(box_list[i], x_crd, y_crd, z_crd);
        }

        int total_volume = x_crd.length() * y_crd.length() * z_crd.length();
        int x_num = x_crd.number(), y_num = y_crd.number(), z_num = z_crd.number();
        auto result = dfs(point(0, 0, 0), x_crd, y_crd, z_crd);
        result.second = total_volume - result.second;
        cout << result.first << " " << result.second << endl;
    }
}
#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>
#include <vector>
#include <algorithm>
#include <iterator>
#include <map>

using namespace std;

class Loc_map
{
public:
    Loc_map(string name,double x1,double y1,double x2,double y2):map_name(name){
        this->x1 = min(x1,x2);
        this->x2 = max(x1,x2);
        this->y1 = min(y1,y2);
        this->y2 = max(y1,y2);
        this->center_x = (x1 + x2) / 2.0;
        this->center_y = (y1 + y2) / 2.0;
    }
    ~Loc_map(){};

    bool operator==(const Loc_map& Others) const{
        if (this->area() == Others.area()){
            return true;
        }
        else{
            return false;
        }
    };

    bool operator<(const Loc_map& Others) const{
        if (this->area() < Others.area()){
           return true; 
        }
        else{
            return false;
        }
    }

    double area() const {
        return abs(x1-x2) * abs(y1-y2);
    }

    double dist_center2(double x,double y) const{
        double dx = abs(x - center_x);
        double dy = abs(y - center_y);
        return dx * dx + dy * dy;
    }

    double dist_right_corner2(double x, double y)const{
        double dx = abs(x - x2);
        double dy = abs(y - y2);
        return dx * dx + dy * dy;
    }
    double aspect_ratio() const{
        return (abs(y2 - y1) / abs(x2 - x1) - 0.75);
    }

    bool point_in_map(double x,double y) {
        if (x < x1 || x > x2 || y < y1 || y > y2 ){
            return false;
        }
        else{
            return true;
        }
    }
    string map_name;
    double x1;
    double y1;
    double x2;
    double y2;
    double center_x;
    double center_y;
};

string find_map(double x,double y,vector<Loc_map>& map_list){
    if (map_list.size()==1){
        return map_list[0].map_name;
    }

    // dist center judge
    map<double, vector<Loc_map *> > dist_map;
    for (auto &map_item : map_list)
    {
        dist_map[map_item.dist_center2(x, y)].push_back(&map_item);
    }
    if (dist_map.begin()->second.size()==1){
        return dist_map.begin()->second[0]->map_name;
    }

    // aspect ratio
    map<double, vector<Loc_map *> > ratio_map;
    for (auto map_ptr : dist_map.begin()->second)
    {
        ratio_map[map_ptr->aspect_ratio()].push_back(map_ptr);
    }
    if (ratio_map.begin()->second.size()==1){
        return ratio_map.begin()->second[0]->map_name;
    }

    // lower right corner
    map<double, vector<Loc_map *> > corner_map;
    for (auto map_ptr : ratio_map.begin()->second)
    {
        corner_map[map_ptr->dist_right_corner2(x,y)].push_back(map_ptr);
    }
    if(corner_map.rbegin()->second.size()==1){
        return corner_map.rbegin()->second[0]->map_name;
    }

    //smallest x1
    Loc_map *samll_map_ptr=corner_map.rbegin()->second[0];
    double smallest_x1=corner_map.rbegin()->second[0]->x1;
    for (auto map_ptr:corner_map.rbegin()->second)
    {
        if (map_ptr->x1 < smallest_x1){
            smallest_x1 = map_ptr->x1;
            samll_map_ptr = map_ptr;
        }
    }
    return samll_map_ptr->map_name;
}

void cout_info(string point,int detail){
    cout << point << " at detail level " << detail << " ";
}

void cout_unkonw(string point,int detail){
    cout_info(point, detail);
    cout << "unknown location" << endl;
}

void cout_no_map(string point,int detail){
    cout_info(point, detail);
    cout << "no map contains that location" << endl;
}

void cout_no_detail(string point,int detail,string map_name){
    cout_info(point, detail);
    cout << "no map at that detail level; using " << map_name << endl;
}

void cout_valid_map(string point,int detail,string map_name){
    cout_info(point, detail);
    cout << "using " << map_name << endl;
}

int main()
{
    //ifstream fin("input.txt");
    //cin.rdbuf(fin.rdbuf());

    string templine;
    // read MAPS
    getline(cin,templine);
    vector<Loc_map> Maps;
    while (getline(cin,templine) && templine != "LOCATIONS")
    {
       stringstream line_split(templine); 
       string name;
       double x1,y1,x2,y2;
       line_split >> name >> x1 >> y1 >> x2 >> y2;
       Maps.push_back(Loc_map(name,x1,y1,x2,y2));
    }
    // read LOCATIONS
    map<string,pair<double,double> > Points;
    while (getline(cin,templine) && templine != "REQUESTS")
    {
        stringstream line_split(templine);
        string name;
        double x,y;
        line_split >> name >> x >> y;
        Points[name]=make_pair(x,y);
    }
    // read REQUESTS
    map<string, map<double, vector<Loc_map> > > table;
    while (getline(cin, templine) && templine != "END")
    {
        stringstream line_split(templine);
        string name;
        int level=0;
        line_split >> name >> level;
        // find unknown point name
        if (Points.count(name) == 0){
            cout_unkonw(name, level);
            continue;
        }
        // create table
        if (table.count(name) ==0){
            for (auto item:Maps){
                if (item.point_in_map(Points[name].first,Points[name].second)){
                    table[name][item.area()].push_back(item);
                }
            }
        };

        // if point not on the map
        if (table[name].size()==0){
            cout_no_map(name, level);
            continue;
        }

        // get no detail
        if (table[name].size() < level){
            string map_name = find_map(Points[name].first,Points[name].second,table[name].begin()->second);
            cout_no_detail(name, level, map_name);

        }
        else{
            auto iter = table[name].rbegin();
            advance(iter, level - 1);
            string map_name = find_map(Points[name].first,Points[name].second,iter->second);
            cout_valid_map(name, level, map_name);
        }
    }

}
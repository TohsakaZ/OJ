#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>
#include <vector>
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

};

int main()
{
    ifstream fin("input.txt");
    cin.rdbuf(fin.rdbuf());

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
    while (getline(cin,templine) && templine != "END")
    {
        stringstream line_split(templine);
        string name;
        int level=0;
        line_split >> name >> level;

    }




}